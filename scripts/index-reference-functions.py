#!/usr/bin/env python3
"""Inventory reference bodies and parse gaps; discovery never implies review."""
import argparse
import ast
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
SOURCE_SUFFIXES = {".cpp", ".cc", ".cxx", ".hpp", ".h", ".c", ".inl", ".inc", ".py", ".ps1"}
ADDRESS = re.compile(r"(?:0x|FUN_)([0-9a-fA-F]{6,8})\b")
PARSER_ANNOTATIONS = {
    "native_recovered/native_exports.cpp": (b"API",),
    "source_reconstruction/core_scheduler/cpu_compare.cpp": (b"__cdecl",),
}
PARSER_INLINE_ASM = {"source_reconstruction/platform_services/cpu_compare.cpp"}


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
    if Path(path).suffix in {".py", ".ps1"}:
        return "tool-or-support"
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


def script_inventory(path, data):
    # Python top-level execution is itself an implementation, even in files
    # without functions. PowerShell gets a whole-file entry and an explicit
    # unresolved function-inventory gap until that file is manually reconciled.
    data.decode("utf-8")  # AST column offsets below refer to original UTF-8 bytes.
    module = path.split("/")[1] if path.startswith("source_reconstruction/") else path.split("/")[0]
    ranges = [("script_module", "<module>", 1, 0, max(1, len(data.splitlines())), 0, len(data))]
    errors = []
    if path.endswith(".py"):
        tree = ast.parse(data, filename=path)
        lines = data.splitlines(keepends=True)
        offsets = [0]
        for line in lines:
            offsets.append(offsets[-1] + len(line))
        for node in ast.walk(tree):
            if not isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef, ast.Lambda)):
                continue
            start, column = node.lineno, node.col_offset
            if getattr(node, "decorator_list", None):
                first = node.decorator_list[0]
                start, column = first.lineno, first.col_offset - 1
            begin = offsets[start - 1] + column
            end = offsets[node.end_lineno - 1] + node.end_col_offset
            ranges.append(("python_" + type(node).__name__, getattr(node, "name", "<lambda>"),
                           start, column, node.end_lineno, begin, end))
    else:
        errors.append(dict(start_line=1, end_line=ranges[0][4],
                           node_type="unsupported_powershell_function_inventory"))
    rows = []
    for kind, name, start, column, end_line, begin, end in ranges:
        identity = f"{path}:{start}:{column}:{kind}:{name}"
        body = data[begin:end]
        rows.append(dict(id=digest(identity.encode())[:20], reference_path=path, module=module,
                         kind=kind, name=name, start_line=start, end_line=end_line,
                         body_sha256=digest(body), file_sha256=digest(data),
                         address_hints=";".join(addresses(body.decode("utf-8"))),
                         role_hint=source_role(path)))
    return rows, dict(path=path, sha256=digest(data), definitions=len(rows),
                      role_hint=source_role(path), parse_errors=errors)


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
        if Path(path).suffix in {".py", ".ps1"}:
            script_rows, file = script_inventory(path, data)
            rows.extend(script_rows)
            files.append(file)
            continue
        # Only manually reconciled annotation sites are normalized. Preserve
        # every byte offset and hash the original body, never the parse view.
        # __cdecl otherwise merges a forward declaration with the next class.
        parse_data = data
        for token in PARSER_ANNOTATIONS.get(path, ()):
            parse_data = re.sub(rb"\b" + token + rb"\b", b" " * len(token), parse_data)
        if path in PARSER_INLINE_ASM:
            # This manually read test file uses five flat MSVC asm statements.
            # The grammar mistakes them for functions and loses their owner.
            # Preserve original source ranges/hashes, including the statements.
            parse_data = re.sub(rb"\b__asm\s*\{[^{}]*\}",
                                lambda match: re.sub(rb"[^\r\n]", b" ", match.group()),
                                parse_data)
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
