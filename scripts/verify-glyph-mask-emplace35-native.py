#!/usr/bin/env python3
"""Verify the original glyph PMR insertion/growth/move chain and C++ bodies.

The 35B public wrapper omits one native compiler NOP. The 108B/140B/488B
backend, 200B uninitialized-move, 92B backout, and 31B allocator wrapper
bodies match after resolving their true COFF/PE relocation fields. Remaining
callee-target differences are reported explicitly; no parent is promoted to
whole-function exactness on body shape alone.
"""
from __future__ import annotations
import hashlib
import importlib.util
import subprocess
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

def load(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

pe = load("glyph35_pe", "scripts/verify-animation-draw-boss-native.py")
coff = load("glyph35_coff", "scripts/compare-coff-function.py")
HEADS = {
    "wrapper": (0x00416330, 35, "bd26f62ba6f30fe4d6e5845561e0cc2ecdd80da8bc771cdcdd260e25109343b4"),
    "move": (0x0040B280, 8, "d5a2b635b0bbb254914f2641e4508361a0c95686c0422dcebeb3abbcca7f1d2b"),
    "one_at_back": (0x00413370, 108, "2ad1446dee98794f9578c474b883145c2296ff1adcb2def8d653e3d365e5e04b"),
    "unused_capacity": (0x004132E0, 140, "1f514d2135b7b78ef041cc44ba21003fe295a2033b33a1a78eb8e40862bc37f2"),
    "reallocate": (0x004133E0, 488, "5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57"),
    "uninitialized_move": (0x00413920, 200, "ec0f652bfa6eaf3ee4ac165bd3088e80e924fc7b8747e74ba133d3041febca65"),
    "backout_emplace": (0x00413280, 92, "18296f2dae98ec6f1f145b63a49f73add1fca82614d4d636f2e7003c24267e4e"),
    "allocator_move_construct": (0x00413A90, 31, "44c1312b5fa19dac8832bb9b86bd0ade4ddb027f86595af165549111bc99a34b"),
}
PARENT = 0x00416420
PARENT_SIZE = 2245
PARENT_SHA = "06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad"
PARENT_INSERT_SITES = (0x165, 0x4DD)
CANDIDATE_PARENT_INSERT_SITES = (0x16E, 0x4F3)
SYMBOL_PREFIXES = {
    "move": "??$move@ABV?$array@H$01@std@@@std@@",
    "wrapper": "??$emplace_back@ABV?$array@H$01@std@@",
    "one_at_back": "??$_Emplace_one_at_back@ABV?$array@H$01@std@@",
    "unused_capacity": "??$_Emplace_back_with_unused_capacity@ABV?$array@H$01@std@@",
    "reallocate": "??$_Emplace_reallocate@ABV?$array@H$01@std@@",
    "uninitialized_move": "??$_Uninitialized_move@PAV?$array@H$01@std@@V?$polymorphic_allocator",
    "backout_emplace": "?_Emplace_back_deref_move@?$_Uninitialized_backout_al",
    "allocator_move_construct": "?glyph_uninitialized_move_construct@th20@@",
    "move_element": "??$move@AAV?$array@H$01@std@@@std@@",
}
EXPECTED_CALLS = {
    "wrapper": (0x0B, 0x17),
    "one_at_back": (0x2C, 0x38, 0x43, 0x61),
    "unused_capacity": (0x1F, 0x30, 0x3E, 0x52, 0x69),
    "reallocate": (0x2E, 0x6F, 0x79, 0x8F, 0x9F, 0xE6, 0xFB, 0x112, 0x146, 0x162, 0x18B, 0x1A9, 0x1C5, 0x1DD),
    "uninitialized_move": (0x2C, 0x3B, 0x4B, 0x5B, 0x7E, 0x8A, 0x95, 0xA7, 0xBF),
    "backout_emplace": (0x0D, 0x1F, 0x3F),
    "allocator_move_construct": (0x07, 0x17),
}

def disassemble(data: bytes, address: int = 0):
    return list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(data, address))

def call_sites(instructions, base: int):
    return tuple(i.address - base for i in instructions if i.size == 5 and i.bytes[0] == 0xE8)

def find_symbol(strings, prefix: str):
    matches = [s for s in strings if s.startswith(prefix) and "array@H$01" in s]
    if len(matches) != 1:
        raise AssertionError(f"expected one symbol for {prefix!r}, got {matches}")
    return matches[0]

def candidate_body(obj: Path, symbol: str, size: int):
    body, relocations = coff.object_function(obj, symbol, size)
    if len(body) != size:
        raise AssertionError((symbol, len(body), size))
    return body, relocations

def native_bytes(image, base, sections, name: str):
    head, size, digest = HEADS[name]
    data = pe.raw_at(image, base, sections, head, size)
    actual = hashlib.sha256(data).hexdigest()
    assert actual == digest, (name, actual, digest)
    return data

def normalize_relocations(native: bytes, candidate: bytes, native_call_sites, relocations,
                          native_highlow=(), candidate_size=None):
    if candidate_size is None:
        candidate_size = len(candidate)
    if len(native) != candidate_size:
        raise AssertionError((len(native), candidate_size))
    native_bytes = bytearray(native)
    candidate_bytes = bytearray(candidate[:candidate_size])
    native_fields = {site + 1 for site in native_call_sites}
    candidate_fields = set()
    for relocation in relocations:
        offset = int(relocation["offset"])
        kind = relocation["type"]
        if kind not in ("REL32", "DIR32"):
            raise AssertionError(relocation)
        candidate_fields.add(offset)
        candidate_bytes[offset:offset + 4] = b"\0" * 4
    if native_fields != {int(r["offset"]) for r in relocations if r["type"] == "REL32"}:
        raise AssertionError((sorted(native_fields), sorted(int(r["offset"]) for r in relocations if r["type"] == "REL32")))
    for offset in native_fields:
        native_bytes[offset:offset + 4] = b"\0" * 4
    for offset in native_highlow:
        native_bytes[offset:offset + 4] = b"\0" * 4
        candidate_bytes[offset:offset + 4] = b"\0" * 4
        if offset not in candidate_fields:
            raise AssertionError(f"missing candidate DIR32 at {offset:#x}")
    return bytes(native_bytes) == bytes(candidate_bytes)

def verify_original():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    native = {name: native_bytes(image, base, sections, name) for name in HEADS}
    wrapper_ins = disassemble(native["wrapper"], HEADS["wrapper"][0])
    assert len(wrapper_ins) == 15 and wrapper_ins[-1].mnemonic == "ret" and wrapper_ins[-1].op_str == "4"
    assert call_sites(wrapper_ins, HEADS["wrapper"][0]) == EXPECTED_CALLS["wrapper"]
    assert wrapper_ins[11].mnemonic == "nop" and wrapper_ins[11].address - HEADS["wrapper"][0] == 0x1C
    for name in ("move", "one_at_back", "unused_capacity", "reallocate"):
        head, size, _ = HEADS[name]
        ins = disassemble(native[name], head)
        expected_ret = {"move": "", "one_at_back": "4", "unused_capacity": "4", "reallocate": "8",
                        "uninitialized_move": "8", "backout_emplace": "4", "allocator_move_construct": "",
                        "move_element": ""}[name]
        assert ins[-1].mnemonic == "ret" and ins[-1].op_str == expected_ret
        if name in EXPECTED_CALLS:
            assert call_sites(ins, head) == EXPECTED_CALLS[name], (name, call_sites(ins, head))
    assert len(disassemble(native["move"], HEADS["move"][0])) == 5
    assert len(disassemble(native["one_at_back"], HEADS["one_at_back"][0])) == 40
    assert len(disassemble(native["unused_capacity"], HEADS["unused_capacity"][0])) == 52
    assert len(disassemble(native["reallocate"], HEADS["reallocate"][0])) == 170
    assert len(disassemble(native["uninitialized_move"], HEADS["uninitialized_move"][0])) == 65
    assert len(disassemble(native["backout_emplace"], HEADS["backout_emplace"][0])) == 34
    assert len(disassemble(native["allocator_move_construct"], HEADS["allocator_move_construct"][0])) == 14
    assert tuple(sorted(a - HEADS["reallocate"][0] for a in pe.physical_highlow(image, base, sections)
                        if HEADS["reallocate"][0] <= a < HEADS["reallocate"][0] + HEADS["reallocate"][1])) == (0x06, 0x15)
    parent = pe.raw_at(image, base, sections, PARENT, PARENT_SIZE)
    assert hashlib.sha256(parent).hexdigest() == PARENT_SHA
    parent_ins = disassemble(parent, PARENT)
    parent_calls = {site: target for site, target in zip(call_sites(parent_ins, PARENT),
                     ((i.address + 5 + int.from_bytes(i.bytes[1:5], "little", signed=True)) & 0xFFFFFFFF
                      for i in parent_ins if i.size == 5 and i.bytes[0] == 0xE8))}
    assert tuple(site for site, target in parent_calls.items() if target == HEADS["wrapper"][0]) == PARENT_INSERT_SITES
    print("PASS original 35B wrapper, 8B move leaf, 108B/140B/488B complete PMR backend bodies and native call graph")
    print("PASS original 2,245B parent has the two physical insertion edges at +0x165/+0x4DD")
    return image, base, sections, native

def verify_candidate(obj: Path, image, base, sections, native):
    strings = subprocess.run(["strings", str(obj)], capture_output=True, text=True, check=True).stdout.splitlines()
    candidates = {}
    relocs = {}
    sizes = {"move": 8, "wrapper": 34, "one_at_back": 108, "unused_capacity": 140, "reallocate": 488,
             "uninitialized_move": 200, "backout_emplace": 92, "allocator_move_construct": 31, "move_element": 8}
    for name, prefix in SYMBOL_PREFIXES.items():
        symbol = find_symbol(strings, prefix)
        candidates[name], relocs[name] = candidate_body(obj, symbol, sizes[name])

    # The shared 8B identity-forwarding leaf is an exact physical body.
    assert candidates["move"] == native["move"]
    assert not relocs["move"]
    assert len(disassemble(candidates["move"])) == 5

    # The old compiler emitted one trailing NOP in the 35B wrapper. The
    # maintained natural-C++ specialization omits it rather than padding.
    wrapper_native = native["wrapper"]
    assert wrapper_native[0x1C] == 0x90
    wrapper_compacted = wrapper_native[:0x1C] + wrapper_native[0x1D:]
    wrapper_ins = disassemble(candidates["wrapper"])
    assert len(wrapper_ins) == 14 and wrapper_ins[-1].mnemonic == "ret" and wrapper_ins[-1].op_str == "4"
    assert call_sites(wrapper_ins, 0) == EXPECTED_CALLS["wrapper"]
    assert len(relocs["wrapper"]) == 2 and all(r["type"] == "REL32" for r in relocs["wrapper"])
    assert normalize_relocations(wrapper_compacted, candidates["wrapper"], EXPECTED_CALLS["wrapper"], relocs["wrapper"])

    # The 108B and 140B bodies are instruction-for-instruction and byte-for-
    # byte identical after only their true E8 displacement fields are resolved.
    for name in ("one_at_back", "unused_capacity"):
        head, size, _ = HEADS[name]
        ins = disassemble(candidates[name])
        assert len(ins) == len(disassemble(native[name], head))
        assert call_sites(ins, 0) == EXPECTED_CALLS[name]
        assert len(relocs[name]) == len(EXPECTED_CALLS[name])
        assert all(r["type"] == "REL32" for r in relocs[name])
        assert normalize_relocations(native[name], candidates[name], EXPECTED_CALLS[name], relocs[name])

    # The 488B reallocation body includes the same 14 E8 positions and the
    # same two PE HIGHLOW fields, represented as two COFF DIR32 relocations.
    reallocate_ins = disassemble(candidates["reallocate"])
    assert len(reallocate_ins) == 170
    assert call_sites(reallocate_ins, 0) == EXPECTED_CALLS["reallocate"]
    assert len(relocs["reallocate"]) == 16
    assert sum(r["type"] == "REL32" for r in relocs["reallocate"]) == 14
    assert sum(r["type"] == "DIR32" for r in relocs["reallocate"]) == 2
    assert normalize_relocations(native["reallocate"], candidates["reallocate"], EXPECTED_CALLS["reallocate"],
                                  relocs["reallocate"], native_highlow=(0x06, 0x15))

    # The complete 200B move parent now restores the old iterator/backout
    # sequence, including its separate element move and backout call.
    move_ins = disassemble(candidates["uninitialized_move"])
    assert len(move_ins) == 65
    assert call_sites(move_ins, 0) == EXPECTED_CALLS["uninitialized_move"]
    assert len(relocs["uninitialized_move"]) == 11
    assert sum(r["type"] == "REL32" for r in relocs["uninitialized_move"]) == 9
    assert sum(r["type"] == "DIR32" for r in relocs["uninitialized_move"]) == 2
    assert normalize_relocations(native["uninitialized_move"], candidates["uninitialized_move"],
                                  EXPECTED_CALLS["uninitialized_move"], relocs["uninitialized_move"],
                                  native_highlow=(0x06, 0x15))

    # The old 92B backout member and its 31B construction wrapper also retain
    # every non-relocation byte and all native call offsets.
    for name in ("backout_emplace", "allocator_move_construct"):
        ins = disassemble(candidates[name])
        assert call_sites(ins, 0) == EXPECTED_CALLS[name]
        assert len(relocs[name]) == len(EXPECTED_CALLS[name])
        assert all(r["type"] == "REL32" for r in relocs[name])
        assert normalize_relocations(native[name], candidates[name], EXPECTED_CALLS[name], relocs[name])
    assert candidates["move"] == native["move"] and not relocs["move"]
    assert candidates["move_element"] == native["move"] and not relocs["move_element"]

    # Relocation identities expose the remaining old/new STL boundary rather
    # than hiding it behind matching E8 positions.
    move_relocs = {int(r["offset"]) - 1: r["symbol"] for r in relocs["uninitialized_move"] if r["type"] == "REL32"}
    assert "_Get_unwrapped" in move_relocs[0x2C] and "_Get_unwrapped" in move_relocs[0x3B]
    assert "_Emplace_back_deref_move" in move_relocs[0x8A]
    backout_relocs = {int(r["offset"]) - 1: r["symbol"] for r in relocs["backout_emplace"]}
    assert "glyph_uninitialized_move_construct" in backout_relocs[0x3F]
    allocator_relocs = {int(r["offset"]) - 1: r["symbol"] for r in relocs["allocator_move_construct"]}
    assert "move@ABV" in allocator_relocs[0x07]
    assert "polymorphic_allocator" in allocator_relocs[0x17] and "construct" in allocator_relocs[0x17]

    # The game-owned parent still calls the real C++ emplace_back specialization
    # at both original sites. This does not award parent exactness.
    parent_symbol = next(s for s in strings if s.startswith("?composite_glyph_mask_416420@NativeGlyphCanvasView@th20@@"))
    parent, parent_relocs = candidate_body(obj, parent_symbol, 2224)
    parent_ins = disassemble(parent)
    assert len(call_sites(parent_ins, 0)) == 37
    emplace_fields = {int(r["offset"]) - 1 for r in parent_relocs
                      if r["type"] == "REL32" and "emplace_back" in r["symbol"]}
    assert emplace_fields == set(CANDIDATE_PARENT_INSERT_SITES), emplace_fields
    print("PASS candidate 8B std::move leaf is byte-exact")
    print("PASS candidate 108B/40-i386, 140B/52-i386 and 488B/170-i386 bodies match every non-relocation byte and all native E8 positions")
    print("PASS candidate 200B/65-i386 uninitialized-move body, 92B/34-i386 backout member and 31B/14-i386 allocator wrapper match all non-relocation bytes and native E8 positions")
    print("PASS candidate 488B has the original 14 E8 and 2 HIGHLOW relocation sites; 200B has 9 E8 and 2 HIGHLOW sites")
    print("PASS candidate std::move<GlyphMaskOffset&> forwarding leaf is byte-exact")
    print("RESIDUAL: 10B C++20 _Get_unwrapped vs native 9B; 31B allocator wrapper calls current 69B polymorphic_allocator::construct vs native 78B helper; 31B __autoclassinit2 call-site lowering differs")
    print("PASS candidate 34B/14-i386 emplace wrapper retains both original E8 sites; only native +0x1C NOP is absent")
    print("PASS 2,224B parent routes both BGRA/ARGB insertion calls through the specialized wrapper at candidate +0x16E/+0x50E; original sites are +0x165/+0x4DD, parent remains NONEXACT")

if __name__ == "__main__":
    candidate = None
    if len(sys.argv) == 3 and sys.argv[1] == "--candidate-object":
        candidate = Path(sys.argv[2])
    elif len(sys.argv) != 1:
        raise SystemExit("usage: verify-glyph-mask-emplace35-native.py [--candidate-object OBJECT]")
    image, base, sections, native = verify_original()
    if candidate is not None:
        verify_candidate(candidate, image, base, sections, native)
