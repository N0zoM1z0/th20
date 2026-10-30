#!/usr/bin/env python3
"""Immutable native 60-element ribbon point/radius end helpers and 538B edges."""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "pe", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
BODIES = ((0x0045DCA0, 0xF0, 0x0045E83F),
          (0x0045DCC0, 0x1E0, 0x0045E92A))
PARENT = (0x0045E800, 538)
PARENT_CALLS = {
    0x034: 0x0040BDA0, 0x03F: 0x0045DCA0,
    0x069: 0x004298E0, 0x110: 0x00429210,
    0x11F: 0x0040BDA0, 0x12A: 0x0045DCC0,
    0x162: 0x00414580, 0x173: 0x004292E0,
    0x195: 0x00439330, 0x1BE: 0x004530C0,
    0x1DC: 0x0045D670, 0x1F7: 0x0045D670,
    0x20C: 0x005429EE,
}
PARENT_HIGHLOW = {
    0x01A: 0x005B25C0, 0x065: 0x005BA4C4,
    0x07A: 0x0056C8D0, 0x0A9: 0x0056C8E0,
    0x0C2: 0x0056C8E0, 0x0D8: 0x0056C8E0,
    0x0ED: 0x0056C8E0, 0x1A1: 0x0056E0F0,
    0x1A9: 0x0056C8D0, 0x1B1: 0x0056EE48,
}


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    highlow = pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    parent = list(decoder.disasm(pe.raw_at(image, base, sections, *PARENT), PARENT[0]))
    assert len(parent) == 149
    assert parent[-1].address + parent[-1].size == PARENT[0] + PARENT[1]
    assert (parent[-1].mnemonic, parent[-1].op_str) == ("ret", "4")
    observed_calls = {
        ins.address - PARENT[0]: (ins.address + ins.size + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in parent if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    assert observed_calls == PARENT_CALLS, (observed_calls, PARENT_CALLS)
    parent_highlow = {
        addr - PARENT[0]: struct.unpack("<I", pe.raw_at(image, base, sections, addr, 4))[0]
        for addr in highlow if PARENT[0] <= addr < PARENT[0] + PARENT[1]
    }
    assert parent_highlow == PARENT_HIGHLOW, (parent_highlow, PARENT_HIGHLOW)
    parent_ins = {(ins.address, ins.mnemonic, ins.op_str) for ins in parent}
    assert any("0x2d0" in args for _,op,args in parent_ins if op == "add")
    assert any("0x3b" in args for _,op,args in parent_ins if op == "push")
    for head, byte_count, caller in BODIES:
        decoded = list(decoder.disasm(pe.raw_at(image, base, sections, head, 19), head))
        assert len(decoded) == 9 and decoded[-1].address + decoded[-1].size == head + 19
        assert (decoded[-1].mnemonic, decoded[-1].op_str) == ("ret", "")
        assert any((ins.mnemonic, ins.op_str) == ("add", f"eax, {byte_count:#x}") for ins in decoded)
        assert not any(ins.bytes[0] == 0xE8 for ins in decoded)
        assert not any(head <= pos < head + 19 for pos in highlow)
        assert any(ins.address == caller for ins in parent)
        call = pe.raw_at(image, base, sections, caller, 5)
        assert call[0] == 0xE8
        target = (caller + 5 + struct.unpack_from("<i", call, 1)[0]) & 0xFFFFFFFF
        assert target == head, (hex(caller), hex(target))
        print(f"PASS 19B/9 i386 original at {head:#010x}: end +{byte_count:#x}, E8 parent {caller:#010x}")
    print("PASS complete original 538B/149 i386 parent boundary, radius +0x2D0 and closing index 59")
    print("PASS entire 538B original: 13 native E8 and 10 PE HIGHLOW sites/target roles")
    print("NOTE the 538B parent is SOURCE-ABSENT/NONEXACT; helper exactness is independent")


if __name__ == "__main__":
    verify()
