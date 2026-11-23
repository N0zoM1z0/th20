#!/usr/bin/env python3
"""Verify Enemy inline Laser mutation opcodes 705-710/714 and six native setter leaves."""
from __future__ import annotations

import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE = ROOT / "resources/th20.exe"
PE_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
IMAGE_BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
COMMON_EPILOGUE = 0x004963DF

CASES = {
    705: (157, 0x00495083, 0x00495122, 159, 33,
          "41440f8b4e79359f125ba2d429c6360f2b3b291ec1cb9840d76f678257563251",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x00422E10, 0x004AAFB0, 0x004AAFB0, 0x0049C800]),
    706: (158, 0x00495122, 0x0049518F, 109, 24,
          "ed7223d01b757a05009d31f9b6756af05bd6cc6fb91c614bbdc03e43db3d0416",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x004AAFB0, 0x0049C900]),
    707: (159, 0x0049518F, 0x004951FC, 109, 24,
          "ed1a4f26d5b2bc90340631e0777c66d1f9c7b90499df5c0e4c3221f9e307e876",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x004AAFB0, 0x0049CB10]),
    708: (160, 0x004951FC, 0x00495269, 109, 24,
          "e74240d89f3ec1008e83b00828e563e02727b150fbb9df1255f0ccd953f752d3",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x004AAFB0, 0x0049C8C0]),
    709: (161, 0x00495269, 0x004952D6, 109, 24,
          "5b8e3874b8924a045c60e3690c38df332452dc6953cb19020cb0016505cdc676",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x004AAFB0, 0x0049C8E0]),
    710: (162, 0x00494F52, 0x00494FD3, 129, 29,
          "ff435ada8dd7ad827a823624a336c8a823d72b5f471cdecb99330d4a65da19ad",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x0049C500]),
    714: (166, 0x004952D6, 0x0049535E, 136, 29,
          "1897fa2091dedde2fa20479d159c7f646dbf5933a24fdcbb3d5b4f320a5d426e",
          [0x0041CA90, 0x004AB080, 0x00498FF0, 0x004AB080]),
}

SETTERS = {
    "set_handle": (0x0049C500, 25, "6af0c7ac6c55d4808cd182a8fd1c418910595a097801ed01158299f077b91ac3", "0x8c"),
    "set_parameter_vector_704": (0x0049C800, 40, "dce097f13352fa259f44f172adb9277adb1967861a5ed00047859c7d7e31b72d", "0x704"),
    "set_angle": (0x0049C8C0, 26, "44524ef0ea8c78454388285f09b121a5423b8752940e37a5a693e984965b2e63", "0x70"),
    "set_parameter_field_714": (0x0049C8E0, 29, "9f77fdaa65295e9a2067dc1f138efdd10339a3d920db049a1ae3751146c4481e", "0x714"),
    "set_field_7c": (0x0049C900, 26, "229f900a36cd8ed4de47bb9145a200b2eecdce3e35041ea73d082ecc9c226f51", "0x7c"),
    "set_speed": (0x0049CB10, 26, "0fa8e9c8fedd8bc807b299c698a4116cd67875ce0a9a4b9ccd1200b3a4f5205e", "0x78"),
}

EXPECTED_RELOCS = [
    "?laser_controller@Context@th20",
    "?integer_argument@EnemyState@th20",
    "?find_laser@LaserController@th20",
    "??0Vector3@th20",
    "?float_argument@EnemyState@th20",
    "?float_argument@EnemyState@th20",
    "?set_parameter_vector_704@Laser@th20",
    "?laser_controller@Context@th20",
    "?integer_argument@EnemyState@th20",
    "?find_laser@LaserController@th20",
    "?float_argument@EnemyState@th20",
    "?set_field_7c@Laser@th20",
    "?set_speed@Laser@th20",
    "?set_angle@Laser@th20",
    "?set_parameter_field_714@Laser@th20",
    "?laser_controller@Context@th20",
    "?integer_argument@EnemyState@th20",
    "?find_laser@LaserController@th20",
    "?set_handle@Laser@th20",
    "?laser_controller@Context@th20",
    "?integer_argument@EnemyState@th20",
    "?find_laser@LaserController@th20",
    "?integer_argument@EnemyState@th20",
    "@__security_check_cookie@4",
]


def run(*args: str) -> str:
    return subprocess.run(args, cwd=ROOT, check=True, text=True, capture_output=True).stdout


def main() -> None:
    pe_bytes = PE.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == PE_SHA256
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    selector = pe.get_data(SELECTOR_TABLE - IMAGE_BASE, 704)
    pointers = pe.get_data(POINTER_TABLE - IMAGE_BASE, 174 * 4)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    total_bytes = total_instructions = total_direct_calls = 0

    for opcode, (index, start, end, size, count, digest, expected_calls) in CASES.items():
        assert selector[opcode - 300] == index, (opcode, selector[opcode - 300], index)
        assert int.from_bytes(pointers[index * 4:index * 4 + 4], "little") == start
        native = pe.get_data(start - IMAGE_BASE, end - start)
        assert len(native) == size
        assert hashlib.sha256(native).hexdigest() == digest, (opcode, hashlib.sha256(native).hexdigest())
        insns = list(decoder.disasm(native, start))
        assert len(insns) == count, (opcode, len(insns), count)
        assert insns[0].address == start
        assert insns[-1].address + insns[-1].size == end
        assert insns[-1].mnemonic == "jmp" and int(insns[-1].op_str, 16) == COMMON_EPILOGUE
        direct = [int(i.op_str, 16) for i in insns if i.mnemonic == "call" and i.op_str.startswith("0x")]
        assert direct == expected_calls, (opcode, direct, expected_calls)
        indirect = [i for i in insns if i.mnemonic == "call" and not i.op_str.startswith("0x")]
        if opcode == 710:
            assert len(indirect) == 1
            assert indirect[0].address == 0x00494FB8
            assert indirect[0].op_str == "dword ptr [ebp - 0xecc]"
            text = "\n".join(f"{i.mnemonic} {i.op_str}" for i in insns)
            assert "mov edx, dword ptr [ecx + 0x44]" in text
            assert text.index("call dword ptr [ebp - 0xecc]") < text.index("call 0x49c500")
        elif opcode == 714:
            assert len(indirect) == 1
            assert indirect[0].address == 0x00495352
            assert indirect[0].op_str == "dword ptr [ebp - 0xf10]"
            text = "\n".join(f"{i.mnemonic} {i.op_str}" for i in insns)
            assert "mov eax, dword ptr [edx + 0xc]" in text
            assert text.index("mov eax, dword ptr [edx + 0xc]") < text.rindex("call 0x4ab080")
            assert text.rindex("call 0x4ab080") < text.index("call dword ptr [ebp - 0xf10]")
        else:
            assert not indirect
        total_bytes += size
        total_instructions += count
        total_direct_calls += len(direct)

    assert (total_bytes, total_instructions, total_direct_calls) == (860, 187, 35)

    # Three native Laser vtables share the no-op +0x0C slot; the Beam vtable
    # routes that same virtual slot to its bit-zero flag override.
    vtable_addresses = (0x00571148, 0x00571214, 0x005712E8, 0x00571374)
    flag_targets = [
        int.from_bytes(pe.get_data(address - IMAGE_BASE + 0x0C, 4), "little")
        for address in vtable_addresses
    ]
    assert flag_targets == [0x0040EC90, 0x0040EC90, 0x0040EC90, 0x004D7D20]
    default_flag = pe.get_data(0x0040EC90 - IMAGE_BASE, 13)
    assert hashlib.sha256(default_flag).hexdigest() == "8a964d1d7ff7ce1a3c60997027339b1b12723566ff413f0bb34cb92f56441d3a"
    beam_flag = pe.get_data(0x004D7D20 - IMAGE_BASE, 42)
    assert hashlib.sha256(beam_flag).hexdigest() == "006557136769450e257f9674a8b40724d65d97d887b0bf2de49357dfee41d63e"
    beam_flag_text = "\n".join(f"{i.mnemonic} {i.op_str}" for i in decoder.disasm(beam_flag, 0x004D7D20))
    assert "and eax, 1" in beam_flag_text and "and edx, 0xfffffffe" in beam_flag_text
    assert "or edx, eax" in beam_flag_text and "0x730" in beam_flag_text

    # The base no-op's physical address is already owned by the folded STL
    # identity; the Beam override is semantic reconstruction, not a second
    # exact row or duplicate credit.
    function_inventory = (ROOT / "config/functions.csv").read_text(encoding="utf8")
    assert "0x0040EC90,13,0x0040EC9C,FUN_0040ec90,std::_Iterator_base0::_Adopt" in function_inventory
    assert "0x004D7D20,42,0x004D7D49,FUN_004d7d20,th20::LaserBeamInf::set_parameter_flag,LaserBeamInf,reconstructed" in function_inventory
    assert "th20::Laser::set_parameter_flag" not in function_inventory

    # Pin the six leaf targets used by the inline parent cases, independently
    # of the helper implementation and its source names.
    for name, (address, size, digest, store_offset) in SETTERS.items():
        native = pe.get_data(address - IMAGE_BASE, size)
        assert len(native) == size and hashlib.sha256(native).hexdigest() == digest
        insns = list(decoder.disasm(native, address))
        assert insns[-1].mnemonic == "ret" and insns[-1].op_str == "4"
        text = "\n".join(f"{i.mnemonic} {i.op_str}" for i in insns)
        assert store_offset in text, (name, store_offset, text)

    functions = (ROOT / "config/functions.csv").read_text(encoding="utf8")
    assert "0x0040EC90,13,0x0040EC9C,FUN_0040ec90,std::_Iterator_base0::_Adopt" in functions
    assert "th20::Laser::set_parameter_flag" not in functions
    assert "0x004D7D20,42,0x004D7D49,FUN_004d7d20,th20::LaserBeamInf::set_parameter_flag,LaserBeamInf,reconstructed" in functions
    assert "static_assert(offsetof(LaserType3Parameters, flags) == 0x38);" in (ROOT / "src/LaserParameters.hpp").read_text(encoding="utf8")

    source = (ROOT / "src/EnemyStateLaserOpcode.cpp").read_text(encoding="utf8")
    laser_methods = (ROOT / "src/LaserCommandMethods.cpp").read_text(encoding="utf8")
    assert "parameters.flags = (value & 1u) | (parameters.flags & ~1u);" in laser_methods
    assert "execute_enemy_laser_mutation_opcode(*this, opcode)" in (ROOT / "src/EnemyStateExecuteOpcode.cpp").read_text(encoding="utf8")
    begin = source.index("bool execute_enemy_laser_mutation_opcode")
    end = source.index("bool execute_enemy_laser_opcode", begin)
    helper = source[begin:end]
    for fragment in (
        "case 705:", "state.context->laser_controller()", "state.integer_argument(0)",
        "controller->find_laser(handle)", "Vector3 value;", "state.float_argument(1)",
        "state.float_argument(2)", "laser->set_parameter_vector_704(value)",
        "case 706:", "case 707:", "case 708:", "case 709:",
        "if (laser == nullptr) return true;", "const float value = state.float_argument(1);",
        "laser->set_field_7c(value)", "laser->set_speed(value)",
        "laser->set_angle(value)", "laser->set_parameter_field_714(value)",
        "case 710:", "(void)laser->erase(0, 0);", "laser->set_handle(0);",
        "case 714:", "laser->set_parameter_flag(static_cast<std::uint32_t>(state.integer_argument(1)))",
    ):
        assert fragment in helper, fragment
    case705 = helper[helper.index("case 705:"):helper.index("case 706:")]
    assert case705.index("laser_controller()") < case705.index("integer_argument(0)")
    assert case705.index("find_laser(handle)") < case705.index("float_argument(1)") < case705.index("float_argument(2)") < case705.index("set_parameter_vector_704")
    scalar = helper[helper.index("case 706:"):helper.index("case 710:")]
    assert scalar.index("find_laser(handle)") < scalar.index("if (laser == nullptr)") < scalar.index("float_argument(1)")
    case710 = helper[helper.index("case 710:"):helper.index("default:")]
    assert case710.index("find_laser(handle)") < case710.index("erase(0, 0)") < case710.index("set_handle(0)")
    case714 = helper[helper.index("case 714:"):helper.index("default:")]
    assert case714.index("find_laser(handle)") < case714.index("set_parameter_flag") < case714.index("integer_argument(1)")

    tests = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    for fragment in (
        "set_packet(705,", "laser_705_second_float_threw", "run_laser_scalar_setter(706",
        "run_laser_scalar_setter(707", "run_laser_scalar_setter(708", "run_laser_scalar_setter(709",
        "read_native_laser_field<float>(laser_706, 0x714)",
        "set_packet(710,", "laser_710.handle_during_erase == 0x71012345u",
        "laser_710.handle == 0", "DispatchTestLaserAlternateFlag",
        "retarget_context_and_laser_vtable_during_integer_read",
        "dispatch_laser_vtable_retarget_target", "laser_714_alternate.alternate_flag_calls == 0",
        "laser_714_flag_operand_threw", "class DispatchTestLaser : public LaserBeamInf",
        "LaserBeamInf::set_parameter_flag(value)",
        "laser_714_primary.parameters.flags == 0xa5a5a5a5u",
        "laser_714_primary.parameters.flags == 0xa5a5a5a4u",
    ):
        assert fragment in tests, fragment

    helper_dump = run("objdump", "-dr", "build/core223-canonical/EnemyStateLaserOpcode.obj")
    marker = "<?execute_enemy_laser_mutation_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:"
    assert marker in helper_dump
    function = helper_dump.split(marker, 1)[1].split("Disassembly of section", 1)[0]
    relocs = re.findall(r"DISP32\s+([^\r\n]+)", function)
    assert len(relocs) == len(EXPECTED_RELOCS), (relocs, EXPECTED_RELOCS)
    for actual, expected in zip(relocs, EXPECTED_RELOCS):
        assert expected in actual, (actual, expected)
    assert "call   *-0x48(%ebp)" in function
    assert "call   *-0x58(%ebp)" in function
    assert function.index("call   *-0x48(%ebp)") < function.index("?set_handle@Laser@th20")
    find_laser = function.rindex("?find_laser@LaserController")
    slot_capture = function.index("mov    0xc(%ecx),%edx", find_laser)
    second_integer = function.index("?integer_argument@EnemyState", find_laser + 1)
    flag_call = function.index("call   *-0x58(%ebp)")
    assert find_laser < slot_capture < second_integer < flag_call

    # The six leafs are independent exact units, not merely a structural
    # disassembly match. Rebuild one cold source object and replay every body.
    replay = run(sys.executable, "scripts/replay-exact-units.py", "--source", "src/LaserCommandMethods.cpp")
    for name, (_, size, _, _) in SETTERS.items():
        assert f"{name}: exact ({size}/{size} bytes)" in replay, replay
    assert "Exact replay: 6/6 units, 1 cold objects" in replay

    # The Beam flag override is deliberately reconstructed, not strict exact.
    # Pin its honest structural score after the same cold source-object build.
    diagnostic = subprocess.run(
        [sys.executable, "scripts/compare-coff-function.py",
         "build/gpt-web-laser-canonical/LaserCommandMethods.obj",
         "?set_parameter_flag@LaserBeamInf@th20@@UAEXI@Z", "0x004D7D20", "42", "--json"],
        cwd=ROOT, text=True, capture_output=True)
    assert diagnostic.returncode == 1, diagnostic.stdout + diagnostic.stderr
    beam_result = json.loads(diagnostic.stdout)
    assert beam_result["result"] == "mismatch"
    assert beam_result["size"] == 42 and beam_result["comparable_bytes"] == 42
    assert beam_result["matched_comparable_bytes"] == 39
    assert beam_result["relocation_field_bytes"] == 0

    print("PASS original Enemy inline Laser mutation opcodes 705-710/714: selectors 157-162/166, 860B/187 x86/35 ordered E8 plus slot-0x44 erase and slot-0x0C flag virtual calls")
    print("PASS six original Laser setter leaves: 172/172 native bytes strictly exact as natural C++ with no relocations")
    print("PASS opcode714 vtable map: three Laser families share the 13B no-op slot; Beam +0x730 bit-zero override is natural C++ reconstructed at 39/42 bytes, not strict exact")
    print("PASS 705 Context/handle/find/Vector3/float/float/vector-store order; 706-709 null guard before float and +7C/+78/+70/+714 stores")
    print("PASS 710 virtual erase(0,0) precedes set_handle(0), preserving native handle through erase")
    print("PASS natural C++ COFF mutation helper preserves all 24 ordered relocations, erase slot-0x44 and pre-operand-captured flag slot-0x0C calls")
    print("PASS root host covers 705 shared triplet/exception, 706-709 scalar fields/miss/throw, 710 erase-before-clear, and 714 pre-operand vtable capture plus real Beam flag-bit set/clear")
    print(replay, end="")


if __name__ == "__main__":
    main()
