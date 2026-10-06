#!/usr/bin/env python3
"""Inventory reference bodies and parse gaps; discovery never implies review."""
import argparse
import csv
import hashlib
from importlib.metadata import version
import json
from pathlib import Path
import re
import subprocess

from project import ROOT, load_manifest

FIELDS = ["id", "reference_path", "module", "kind", "name", "start_line",
          "end_line", "body_sha256", "file_sha256", "address_hints", "role_hint"]
SOURCE_SUFFIXES = {".cpp", ".cc", ".cxx", ".hpp", ".h", ".c", ".inl", ".inc"}
ADDRESS = re.compile(r"(?:0x|FUN_)([0-9a-fA-F]{6,8})\b")


def digest(data):
    return hashlib.sha256(data).hexdigest()


def reference_checkout():
    pin = load_manifest("reference.toml")
    reference = ROOT / pin["local_path"]
    head = subprocess.check_output(["git", "-C", str(reference), "rev-parse", "HEAD"], text=True).strip()
    dirty = subprocess.check_output(["git", "-C", str(reference), "status", "--porcelain"], text=True)
    if head != pin["commit"] or dirty:
        raise ValueError("reference function inventory requires the clean pinned checkout")
    paths = subprocess.check_output(["git", "-C", str(reference), "ls-files", "-z"])
    return reference, pin, sorted(path for path in paths.decode().split("\0") if path)


def walk(node):
    yield node
    for child in node.named_children:
        yield from walk(child)


def source_role(path):
    parts = Path(path).parts
    if parts[0] == "incremental":
        return "historical-bridge-or-retained-engine"
    if any(part == "oracle" or part == "tests" or part.endswith("_tests") for part in parts) or any(
            token in Path(path).stem for token in ("test", "compare", "fixture", "cpu_cases")):
        return "test-or-oracle"
    if parts[0] in {"source_reconstruction", "native_recovered"}:
        return "reconstruction-candidate"
    return "tool-or-support"


def function_name(node, data):
    if node.type == "lambda_expression":
        return "<lambda>"
    declarator = node.child_by_field_name("declarator")
    if declarator is None:
        return "<unresolved-declarator>"
    function = next((child for child in walk(declarator) if child.type == "function_declarator"), None)
    if function is not None:
        declarator = function.child_by_field_name("declarator") or function
    while True:
        child = declarator.child_by_field_name("declarator")
        if child is None:
            break
        declarator = child
    return data[declarator.start_byte:declarator.end_byte].decode("utf-8", errors="replace")


def addresses(text):
    return sorted({f"0x{int(match, 16):08X}" for match in ADDRESS.findall(text)
                   if 0x00401000 <= int(match, 16) < 0x0056B480})


def inventory(reference, paths):
    import tree_sitter_cpp
    from tree_sitter import Language, Parser
    lock = load_manifest("tools.lock.toml")["python"]
    for distribution, key in (("tree-sitter", "tree_sitter"), ("tree-sitter-cpp", "tree_sitter_cpp")):
        if version(distribution) != lock[key]:
            raise ValueError(f"reference parser version differs: {distribution}")
    parser = Parser(Language(tree_sitter_cpp.language()))
    rows, files = [], []
    for path in paths:
        if Path(path).suffix not in SOURCE_SUFFIXES:
            continue
        if path.startswith("analysis/ghidra/") or "combined_pseudocode" in path:
            continue
        data = (reference / path).read_bytes()
        # API is an export annotation defined in native_exports.cpp. Blanking
        # this token preserves offsets while allowing ordinary C++ parsing.
        parse_data = re.sub(rb"\bAPI\b", b"   ", data) if path == "native_recovered/native_exports.cpp" else data
        tree = parser.parse(parse_data)
        lines = data.decode("utf-8", errors="replace").splitlines()
        module = path.split("/")[1] if path.startswith("source_reconstruction/") else path.split("/")[0]
        nodes = list(walk(tree.root_node))
        definitions = [node for node in nodes if node.type in {"function_definition", "lambda_expression"}
                       and not any(child.type == "delete_method_clause" for child in node.named_children)]
        errors = [dict(start_line=node.start_point.row + 1, end_line=node.end_point.row + 1,
                       node_type=node.type) for node in nodes if node.type == "ERROR" or node.is_missing]
        files.append(dict(path=path, sha256=digest(data), definitions=len(definitions),
                          role_hint=source_role(path), parse_errors=errors))
        for node in definitions:
            start, end = node.start_point.row + 1, node.end_point.row + 1
            previous = node.prev_named_sibling
            comments = []
            while previous is not None and previous.type == "comment":
                comments.append(data[previous.start_byte:previous.end_byte].decode("utf-8", errors="replace"))
                previous = previous.prev_named_sibling
            # Hints are lexical associations, never accepted target mappings.
            hint_text = "\n".join(comments) + "\n" + "\n".join(lines[start - 1:end])
            name = function_name(node, data)
            identity = f"{path}:{start}:{node.start_point.column}:{node.type}:{name}"
            rows.append(dict(id=digest(identity.encode())[:20], reference_path=path, module=module,
                             kind=node.type, name=name, start_line=start, end_line=end,
                             body_sha256=digest(data[node.start_byte:node.end_byte]), file_sha256=digest(data),
                             address_hints=";".join(addresses(hint_text)), role_hint=source_role(path)))
    return sorted(rows, key=lambda row: (row["reference_path"], row["start_line"], row["id"])), files


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    reference, pin, paths = reference_checkout()
    rows, files = inventory(reference, paths)
    output = ROOT / "config/reference-function-index.csv"
    if args.check:
        with output.open(newline="") as stream:
            current = list(csv.DictReader(stream))
        expected = [{key: str(value) for key, value in row.items()} for row in rows]
        if current != expected:
            raise ValueError("reference body inventory is stale")
    else:
        with output.open("w", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
    file_output = ROOT / "config/reference-source-files.csv"
    file_rows = [dict(reference_path=file["path"], file_sha256=file["sha256"],
                      role_hint=file["role_hint"], definitions=file["definitions"],
                      parse_gap_count=len(file["parse_errors"])) for file in files]
    if args.check:
        with file_output.open(newline="") as stream:
            if list(csv.DictReader(stream)) != [{key: str(value) for key, value in row.items()}
                                               for row in file_rows]:
                raise ValueError("reference source file inventory is stale")
    else:
        with file_output.open("w", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=list(file_rows[0]), lineterminator="\n")
            writer.writeheader()
            writer.writerows(file_rows)
    private = ROOT / ".analysis/reference-functions"
    private.mkdir(parents=True, exist_ok=True)
    gaps = [file for file in files if file["parse_errors"]]
    summary = dict(commit=pin["commit"], files=len(files), definitions=len(rows),
                   parse_gap_files=len(gaps), by_role={role: sum(row["role_hint"] == role for row in rows)
                   for role in sorted({row["role_hint"] for row in rows})})
    (private / "files.json").write_text(json.dumps(files, indent=2) + "\n")
    (private / "parse-gaps.json").write_text(json.dumps(gaps, indent=2) + "\n")
    (private / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary, indent=2))
    print("Inventory only: definitions and lexical hints are unreviewed; parse gaps require manual reconciliation.")


if __name__ == "__main__":
    main()
