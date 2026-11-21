#!/usr/bin/env python3
"""Focused source/host verification for the partial 41,967B Enemy opcode root."""
from __future__ import annotations
import hashlib
import re
import subprocess
from pathlib import Path
import pefile

ROOT=Path(__file__).resolve().parents[1]
ADDRESS=0x0048C010
SIZE=41967
NATIVE_SHA256='e6874e1ee7d7def173d3c4af12934573812db26a5572987ec0fa6fafb24a73f0'

HOST_SOURCES=[
    'tests/enemy_state_dispatch_root.cpp',
    'src/EnemyStateExecuteOpcode.cpp', 'src/EnemyStateMovementOpcode.cpp',
    'src/EnemyState.cpp', 'src/EnemyMovement.cpp', 'src/Enemy.cpp',
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

    root=(ROOT/'src/EnemyStateExecuteOpcode.cpp').read_text()
    movement=(ROOT/'src/EnemyStateMovementOpcode.cpp').read_text()
    assert 'entity->current_runtime->current()' in root
    assert 'execute_enemy_movement_opcode(*this, opcode)' in root
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
    for source in (root,movement):
        for forbidden in ('__asm','__declspec(naked)','_emit','__nop'):
            assert forbidden not in source

    profile=['/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
             '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    for source,obj in (
        ('src/EnemyStateMovementOpcode.cpp','build/core209-canonical/EnemyStateMovementOpcode.obj'),
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
    assert 'PASS whole-root dispatch for movement opcodes 400/404/424/448 and special opcode 560 return' in result.stdout
    print(result.stdout,end='')
    print('PASS immutable native EnemyState::execute_opcode root: 41,967B and SHA-256')
    print('PASS full 49-opcode movement family 400-448 and 14 existing opcode fragments wired')
    print('PASS both new i386 COFF source units compile under locked MSVC profile')
    print('PARTIAL source root only; remaining inline cases open, no strict exact-byte credit')


if __name__=='__main__':
    main()
