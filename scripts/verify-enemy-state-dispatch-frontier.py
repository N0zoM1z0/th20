#!/usr/bin/env python3
"""Focused source/host verification for the partial 41,967B Enemy opcode root."""
from __future__ import annotations
import hashlib
import re
import struct
import subprocess
from pathlib import Path
import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT=Path(__file__).resolve().parents[1]
ADDRESS=0x0048C010
SIZE=41967
NATIVE_SHA256='e6874e1ee7d7def173d3c4af12934573812db26a5572987ec0fa6fafb24a73f0'

HOST_SOURCES=[
    'tests/enemy_state_dispatch_root.cpp',
    'src/EnemyStateExecuteOpcode.cpp', 'src/EnemyStateMovementOpcode.cpp',
    'src/EnemyStatePatternOpcode.cpp', 'src/Session.cpp',
    'src/EnemyState.cpp', 'src/EnemyMovement.cpp', 'src/Enemy.cpp', 'src/PlayerRecord.cpp',
    'src/EnemyScript.cpp', 'src/EnemyVariables.cpp', 'src/EnemySpawn.cpp',
    'src/EnemyHealth.cpp', 'src/EnemyPattern.cpp', 'src/EnemyCounters.cpp',
    'src/EclRuntimeLifetime.cpp', 'src/EclArguments.cpp', 'src/EclLoaderBase.cpp',
    'src/EclLoaderBuffer.cpp', 'src/EclCallSetup.cpp', 'src/Timer.cpp',
    'src/ClockScalar.cpp', 'src/Motion.cpp', 'src/MotionConfiguration.cpp',
    'src/MotionUpdates.cpp', 'src/MotionMath.cpp', 'src/Vector2.cpp',
    'src/Vector3.cpp', 'src/Angle.cpp', 'src/Interpolation.cpp',
    'src/IntegerTriple.cpp', 'src/ScalarMath.cpp', 'src/GameRandom.cpp',
    'src/GameRandomStream.cpp', 'src/GameRandomAngle.cpp', 'src/ScriptStack.cpp',
    'src/ScriptStackCopy.cpp', 'src/Identifier32.cpp', 'src/DiagnosticAllocator.cpp',
    'src/DebugMemoryResource.cpp', 'src/LockRegistry.cpp', 'src/Worker.cpp',
    'src/Context.cpp', 'src/MeshInterfaces.cpp', 'src/TaskInfoConstruction.cpp',
    'src/EclDiagnostic.cpp',
]


def main() -> None:
    pe=pefile.PE(str(ROOT/'resources/th20.exe'),fast_load=True)
    native=pe.get_data(ADDRESS-pe.OPTIONAL_HEADER.ImageBase,SIZE)
    assert len(native)==SIZE
    assert hashlib.sha256(native).hexdigest()==NATIVE_SHA256

    # Re-decode the original compressed opcode selector and each newly wired
    # pattern case from the locked PE. The source fragment is not a standalone
    # native function; these are bounded primary case CFGs in the 41,967B root.
    image_base=pe.OPTIONAL_HEADER.ImageBase
    selector=pe.get_data(0x004966B8-image_base,704)
    pointer_table=pe.get_data(0x00496400-image_base,174*4)
    cases={
        506:(56,0x00491989,0x004919A0,[0x00497270]),
        507:(57,0x004919A0,0x004919EB,[0x004AB080,0x004AB080,0x0049C7B0]),
        572:(117,0x004919EB,0x00491A1B,[0x004AB080,0x0049C4E0]),
        567:(113,0x00491A1B,0x00491A66,[0x004AB080,0x004AB080,0x0049C780]),
        568:(114,0x00491A66,0x00491A96,[0x004AB080,0x0049C6F0]),
        508:(58,0x00491A96,0x00491AFB,[0x004AAFB0,0x004AAFB0,0x0049C830]),
        509:(59,0x00491AFB,0x00491B62,[0x00488850,0x0049C0C0,0x00499350,0x0048BF10]),
        556:(102,0x00491B62,0x00491BB9,[0x0049C0C0,0x00499350,0x0048BF10]),
        510:(60,0x00491BB9,0x00491BF6,[0x004AB080,0x00411570]),
    }
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    for opcode,(index,start,end,expected_calls) in cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    root=(ROOT/'src/EnemyStateExecuteOpcode.cpp').read_text()
    movement=(ROOT/'src/EnemyStateMovementOpcode.cpp').read_text()
    pattern=(ROOT/'src/EnemyStatePatternOpcode.cpp').read_text()
    assert 'entity->current_runtime->current()' in root
    assert 'execute_enemy_movement_opcode(*this, opcode)' in root
    assert 'execute_enemy_pattern_opcode(*this, opcode)' in root
    assert 'if (opcode == 560 && entity->defeat())' in root
    assert 'return 1;' in root
    assert 'return 0;' in root
    assert 'if (execute_enemy_laser_opcode(*this, opcode))' in root
    labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',movement)]
    assert len(labels)==49 and set(labels)==set(range(400,449)),labels
    for helper in (
        'execute_enemy_phase_opcode','execute_enemy_card_start_opcode',
        'execute_enemy_script_pointer_opcode','execute_enemy_animation_spawn_opcode',
        'execute_enemy_controller_setter_opcode','execute_enemy_fog_opcode',
        'execute_enemy_membership_opcode','execute_enemy_mesh_opcode',
        'execute_enemy_queue_copy_opcode','execute_enemy_shot_fire_opcode',
        'execute_enemy_shared_queued_parameters_opcode','execute_enemy_shot_command_opcode',
        'execute_enemy_queued_parameters_opcode','execute_enemy_laser_opcode',
    ):
        assert helper in root,helper
    pattern_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',pattern)]
    assert set(pattern_labels)=={506,507,508,509,510,556,567,568,572},pattern_labels
    assert 'session.field_70_is_two()' in pattern
    assert 'state.pattern.drop(origin, bomb_mark)' in pattern
    for source in (root,movement,pattern):
        for forbidden in ('__asm','__declspec(naked)','_emit','__nop'):
            assert forbidden not in source

    profile=['/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
             '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    for source,obj in (
        ('src/EnemyStateMovementOpcode.cpp','build/core209-canonical/EnemyStateMovementOpcode.obj'),
        ('src/EnemyStatePatternOpcode.cpp','build/core210-canonical/EnemyStatePatternOpcode.obj'),
        ('src/EnemyStateExecuteOpcode.cpp','build/core209-canonical/EnemyStateExecuteOpcode.obj'),
    ):
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),source,obj,*profile],cwd=ROOT,check=True)

    host=ROOT/'build/core209-enemy-dispatch-root-test'
    command=['g++-13','-std=c++20','-O1','-Wall','-Wextra','-Werror',
        '-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-pthread','-Isrc',
        '-fsanitize=address,undefined','-fno-sanitize-recover=all','-fno-sanitize=vptr',
        *HOST_SOURCES,'-o',str(host)]
    subprocess.run(command,cwd=ROOT,check=True)
    result=subprocess.run([str(host)],cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS root dispatch: movement 400/404/424/448, pattern 506-510/556/567/568/572, two-player 509 gate and special 560 return' in result.stdout
    print(result.stdout,end='')
    print('PASS immutable native EnemyState::execute_opcode root: 41,967B and SHA-256')
    print('PASS original compressed dispatch pointers and bounded E8 call maps for all nine EnemyPattern cases')
    print('PASS full 49-opcode movement family 400-448, nine EnemyPattern cases and 14 existing opcode fragments wired')
    print('PASS all three i386 COFF source units compile under locked MSVC profile')
    print('PARTIAL source root only; remaining inline cases open, no strict exact-byte credit')


if __name__=='__main__':
    main()
