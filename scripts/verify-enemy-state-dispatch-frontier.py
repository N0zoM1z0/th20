#!/usr/bin/env python3
"""Focused source/host verification for the partial 41,967B Enemy opcode root."""
from __future__ import annotations
import hashlib
import re
from collections import Counter
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
    'src/EnemyStateExecuteOpcode.cpp', 'src/EnemyStateAnimationFlagsClearOpcode.cpp', 'src/EnemyStateScreenOpcode.cpp', 'src/EnemyStateMovementOpcode.cpp',
    'src/Player.cpp', 'src/PlayerStorage.cpp',
    'src/Rectangle.cpp',
    'src/PlayerDirection.cpp',
    'src/EnemyStatePatternOpcode.cpp', 'src/EnemyStateControlOpcode.cpp', 'src/EnemyStateDynamicParameterOpcode.cpp',
    'src/EnemyStateControllerManagementOpcode.cpp', 'src/EnemyStateTimeOpcode.cpp', 'src/EnemyStateCardOpcode.cpp', 'src/EnemyStateFrontendOpcode.cpp',
    'src/EnemySpawning.cpp', 'src/Card.cpp', 'src/AnimationHandle.cpp', 'src/EclSelection.cpp', 'src/Session.cpp',
    'src/EnemyControllerConstruction.cpp', 'src/EnemyInitialization.cpp', 'src/EnemyData.cpp',
    'src/EnemyState.cpp', 'src/EnemyMovement.cpp', 'src/Enemy.cpp', 'src/PlayerRecord.cpp',
    'src/EnemyScript.cpp', 'src/EnemyScriptAdvance.cpp', 'src/EnemyVariables.cpp', 'src/EnemySpawn.cpp',
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
    'src/Context.cpp', 'src/MeshInterfaces.cpp', 'src/TaskInfoConstruction.cpp', 'src/TaskInfo.cpp', 'src/FunctionChain.cpp',
    'src/EclDiagnostic.cpp',
    'src/EnemyStateDialogueOpcode.cpp',
    'src/EnemyStateShotCommandOpcode.cpp', 'src/EnemyQueuedSelection.cpp', 'src/ShotMetadata.cpp',
    'src/EnemyStateSharedQueuedParametersOpcode.cpp', 'src/EnemyStatePlayerAngleOpcode.cpp',
    'src/EnemyStateBulletLaserCancelOpcode.cpp', 'src/BulletSpatialCancellation.cpp',
    'src/BulletDistance.cpp', 'src/LaserCancelNear.cpp', 'src/LaserBase.cpp', 'src/LaserCancelCircleDefault.cpp',
    'src/EnemyStateLaserOpcode.cpp', 'src/LaserParameters.cpp',
    'src/EnemyStateBulletCancelOpcode.cpp', 'src/BulletRectangleCancellation.cpp',
    'src/RectangleCollisions.cpp', 'src/BulletCollisionHandle.cpp', 'src/CollisionGeometry.cpp',
    'src/AnimationGeometry.cpp',
    'src/Matrix4.cpp', 'src/AnmVariables.cpp',
    'src/EnemyStateMeshOpcode.cpp', 'src/EnemyMesh.cpp',
    'src/EnemyStateQueueCopyOpcode.cpp', 'src/EnemyQueuedRecordAssignment.cpp',
    'src/MeshResourceAccess.cpp',
    'src/EnemyStateAnimationSpawnOpcode.cpp', 'src/EnemyStateFogOpcode.cpp',
    'src/EnemyStateMembershipOpcode.cpp', 'src/EnemyStateControllerSetterOpcode.cpp',
    'src/EnemyStateScriptControlOpcode.cpp', 'src/EclManagerSelect.cpp', 'src/EnemyStateAccessor.cpp',
    'src/Bullet.cpp', 'src/BulletController.cpp', 'src/BulletValues.cpp',
    'src/BulletCancellation.cpp',
    'src/GeometryMetrics.cpp',
    'src/FogValue.cpp', 'src/EffectParameters.cpp',
    'src/SoundInfEnqueue323.cpp', 'src/NativeSoundCommandArrayView.cpp',
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

    # The four queued shot-command opcodes share one 1,457-byte native case.
    # Keep its complete original instruction extent and ordered 29-call map
    # tied to the locked PE, separately from the maintained C++ source fragment.
    shot_index=selector[609-300]
    assert shot_index==130
    assert all(selector[opcode-300]==shot_index for opcode in (609,610,611,612))
    shot_start=struct.unpack_from('<I',pointer_table,shot_index*4)[0]
    shot_end=0x0049378E
    assert shot_start==0x004931DD
    shot_body=pe.get_data(shot_start-image_base,shot_end-shot_start)
    assert len(shot_body)==1457
    assert hashlib.sha256(shot_body).hexdigest()=='f129e860c6aaf09aa107aca146fc85abc1eb021721d052c6e2f7c2430dabb98b'
    shot_instructions=list(decoder.disasm(shot_body,shot_start))
    assert len(shot_instructions)==314
    assert shot_instructions[-1].address+shot_instructions[-1].size==shot_end
    shot_calls=[int(insn.op_str,16) for insn in shot_instructions
                if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
    expected_shot_calls=[
        0x004AB080,0x00498B80,0x0040B280,0x0048B180,0x0040B280,
        0x0048B160,0x004AB080,0x00486600,0x004862F0,0x004AB080,
        0x0047C6C0,0x004AB080,0x0047C6C0,0x004AB080,0x0047C6C0,
        0x004AB080,0x0047C6C0,0x004AB080,0x0047C6C0,0x004AB080,
        0x0047C6C0,0x004AAFB0,0x0047C6C0,0x004AAFB0,0x0047C6C0,
        0x004AAFB0,0x0047C6C0,0x004AAFB0,0x0047C6C0,
    ]
    assert shot_calls==expected_shot_calls,shot_calls

    for opcode,(index,start,end,expected_calls) in cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    animation_flag_cases={
        502:(52,0x00490E09,0x004913C9,[0x004AB080,0x00414F30,0x00414F70,0x00450120]),
        503:(53,0x004913C9,0x00491989,[0x004AB080,0x00414F30,0x00414F70,0x0044FA30]),
    }
    for opcode,(index,start,end,expected_calls) in animation_flag_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    selected_position_case={
        324:(17,0x004960C1,0x004961D5,[0x00412730,0x004AB080,0x00498A80,
            0x0047A2C0,0x004AA980,0x0047A2C0,0x004AA980,0x00499350,
            0x004AA980,0x00499350,0x004AA980]),
    }
    for opcode,(index,start,end,expected_calls) in selected_position_case.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert len(instructions)==53,(opcode,len(instructions))
        assert instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    script_control_cases={
        800:(167,0x00495FC1,0x00496051,
             [0x00412730,0x004AB080,0x00498A80,0x004973C0,0x004972C0,0x00540200]),
        801:(168,0x00495DDE,0x00495E86,
             [0x00412730,0x004AB080,0x00498A80,0x0047A2C0,0x004AA980,0x0047A2C0,0x004AA980]),
        802:(169,0x00495E86,0x00495FC1,
             [0x004AB080,0x00412730,0x00485660,0x004989F0,0x0048BD40,0x004989F0,
              0x0048BD40,0x004973C0,0x004972C0,0x004989F0,0x0048BD40,0x00540200]),
    }
    for opcode,(index,start,end,expected_calls) in script_control_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        expected_instruction_counts={800:30,801:32,802:66}
        assert len(instructions)==expected_instruction_counts[opcode],(opcode,len(instructions))
        assert instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    screen_case={
        517:(67,0x00493F8E,0x00493FF1,[0x004AB080,0x004AB080,0x004AB080,0x004250F0]),
    }
    for opcode,(index,start,end,expected_calls) in screen_case.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    control_cases={
        500:(50,0x00490B7B,0x00490C07,[0x004AAFB0,0x004AAFB0,0x0041CAF0,0x00497CC0]),
        501:(51,0x00490C07,0x00490C38,[0x004AAFB0,0x004AAFB0]),
        504:(54,0x004908D4,0x00490958,[0x004AAFB0,0x004AAFB0,0x004AAFB0,0x004AAFB0]),
        505:(55,0x00490958,0x00490978,[]),
        511:(61,0x00491BF6,0x00491CE5,[0x004AB080,0x0045D650,0x0040C300,0x00411570,0x0040C300,0x0049C4E0,0x0040C300,0x0049C340]),
        512:(62,0x00491D39,0x00491E60,[0x004AB080,0x00412730,0x0049C4B0,0x00412730,0x0049C2E0,0x00412730,0x0049C2E0]),
        513:(63,0x00493B5B,0x00493B74,[0x00423520]),
        515:(65,0x00491E60,0x00491E85,[0x004AB080,0x00423520]),
        526:(76,0x00490978,0x004909C0,[0x004AAFB0]),
        535:(81,0x00491E85,0x00491EAA,[0x004AB080,0x00423520]),
        543:(89,0x00495D20,0x00495D64,[0x004AB080]),
        544:(90,0x00495D64,0x00495D7F,[0x004AB080]),
        546:(92,0x0048C211,0x0048C22C,[0x004AB080]),
        547:(93,0x0048C22C,0x0048C24A,[0x004AB080]),
        557:(103,0x00490D90,0x00490DD3,[0x004AB080]),
        558:(104,0x00490DD3,0x00490DEE,[0x004AAFB0]),
        559:(105,0x00490DEE,0x00490E09,[0x004AAFB0]),
        566:(112,0x00491CE5,0x00491D39,[0x004AB080,0x0045D650,0x0040C300,0x0049C340]),
        563:(109,0x00490C38,0x00490D19,[0x004AB080,0x0041CAF0,0x00497CC0,0x004AB080,0x0041CAF0,0x00497CC0]),
        564:(110,0x00490D19,0x00490D90,[0x00499330,0x0041CAF0,0x00497C60]),
        552:(98,0x0049412F,0x00494170,[0x004AB080]),
    }
    for opcode,(index,start,end,expected_calls) in control_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    management_cases={
        520:(70,0x004940AA,0x0049412F,[0x00412730,0x00485660,0x00412730,0x00485660,0x00412730,0x00485660]),
        525:(75,0x00491EAA,0x00491EC8,[0x00412730,0x004A4A20]),
        545:(91,0x00491EC8,0x00491F0A,[0x00412730,0x004AB080,0x004A4810]),
        565:(111,0x00491F0A,0x00491F28,[0x00412730,0x004A4C20]),
        573:(118,0x00491F28,0x00491F46,[0x00412730,0x004A4E30]),
    }
    for opcode,(index,start,end,expected_calls) in management_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    frontend_cases={
        516:(66,0x00493F3F,0x00493F8E,[0x00499350,0x004AB080,0x00426EB0]),
        519:(69,0x0049407F,0x004940AA,[0x00478160,0x00499110]),
        527:(77,0x004909C0,0x00490A69,[0x004AAFB0,0x004AB080,0x00498F50,0x0040FF90,0x004AB080,0x0049C9C0]),
        534:(80,0x00495773,0x0049579E,[0x004AB080,0x0049C720]),
        548:(94,0x0048C5C1,0x0048C5D2,[0x004B96F0]),
    }
    extended_cases={
        549:(95,0x00495D7F,0x00495DDE,[0x00412730,0x004AB080,0x0049BF00,0x004AA9E0]),
        551:(97,0x00495C1F,0x00495D20,[0x00425CC0,0x004AB080,0x004AB080,0x004AB080,0x0045D650,0x004AAFB0,0x004AAFB0,0x004718D0,0x0049C5B0]),
        553:(99,0x00495860,0x004958A2,[0x00412730,0x004AB080,0x0049C490]),
        554:(100,0x004961D5,0x0049623F,[0x0040C300,0x004AAFB0,0x004AAFB0,0x00486480]),
        555:(101,0x0048C3F4,0x0048C578,[0x004292E0,0x00426EB0,0x00499350,0x004560D0,0x00499350,0x0047A2E0,0x00412730,0x004AAE10,0x00499350,0x004790E0]),
    }
    for opcode,(index,start,end,expected_calls) in extended_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        expected_instruction_counts={549:20,551:58,553:14,554:22,555:81}
        assert len(instructions)==expected_instruction_counts[opcode],(opcode,len(instructions))
        assert instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)
    for opcode,(index,start,end,expected_calls) in frontend_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    global_owner_cases={
        # The native case bodies are adjacent in address space, but their
        # compressed jump-table indices are independently selected above.
        524:(74,0x00495727,0x00495773,[0x004AB080,0x0049C940]),
        575:(120,0x004956EC,0x00495727,[0x00460830,0x004AB080,0x0049C390]),
    }
    for opcode,(index,start,end,expected_calls) in global_owner_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    # Opcode 569 is a reserved selector that points directly at the common
    # return-zero epilogue rather than owning an inline case body.
    assert selector[569-300] == 173
    assert struct.unpack_from('<I',pointer_table,173*4)[0] == 0x004963DF
    epilogue=list(decoder.disasm(pe.get_data(0x004963DF-image_base,0x1F),0x004963DF))
    assert epilogue and epilogue[0].mnemonic == 'xor' and epilogue[0].op_str == 'eax, eax'
    assert epilogue[-1].address + epilogue[-1].size == 0x004963FE

    card_cases={
        523:(73,0x004943C9,0x00494405,[0x00411700,0x004878B0,0x0049C360]),
        536:(82,0x00494405,0x00494423,[0x00411700,0x00497450]),
        537:(83,0x00494423,0x00494441,[0x00411700,0x00497420]),
        561:(107,0x00494441,0x00494483,[0x00411700,0x004AB080,0x0049CA10]),
        562:(108,0x00494398,0x004943C9,[0x004AB080,0x0049C360]),
    }
    for opcode,(index,start,end,expected_calls) in card_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    time_cases={
        538:(84,0x00494483,0x004944C7,[0x004AB080]),
        539:(85,0x0049579E,0x004957BC,[0x0041CA90,0x004D2430]),
        540:(86,0x004957BC,0x00495860,[0x004AB080,0x004AB080]),
        541:(87,0x004958A2,0x004958C3,[0x004AAFB0,0x004292A0]),
        542:(88,0x0049598E,0x00495A9A,[0x004AB080]*4+[0x004640A0]*3+[0x0049CC30]),
        574:(119,0x004963A2,0x004963DF,[0x0049CC30]),
    }
    for opcode,(index,start,end,expected_calls) in time_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    dynamic_cases={
        529:(78,0x00491F46,0x0049201A,[0x004AB080,0x004AA9E0]*4),
        530:(79,0x0049201A,0x00492101,[0x004AAFB0,0x004AA980]*4),
        570:(115,0x00492101,0x00492289,[0x004AB080,0x004AA9E0]*8),
        571:(116,0x00492289,0x00492434,[0x004AAFB0,0x004AA980]*8),
    }
    for opcode,(index,start,end,expected_calls) in dynamic_cases.items():
        assert selector[opcode-300]==index,(opcode,selector[opcode-300],index)
        assert struct.unpack_from('<I',pointer_table,index*4)[0]==start,(opcode,start)
        body=pe.get_data(start-image_base,end-start)
        instructions=list(decoder.disasm(body,start))
        assert instructions and instructions[-1].address+instructions[-1].size==end,(opcode,end)
        calls=[int(insn.op_str,16) for insn in instructions
               if insn.mnemonic=='call' and insn.op_str.startswith('0x')]
        assert calls==expected_calls,(opcode,calls,expected_calls)

    root=(ROOT/'src/EnemyStateExecuteOpcode.cpp').read_text()
    script_control=(ROOT/'src/EnemyStateScriptControlOpcode.cpp').read_text()
    ecl_manager_select=(ROOT/'src/EclManagerSelect.cpp').read_text()
    movement=(ROOT/'src/EnemyStateMovementOpcode.cpp').read_text()
    pattern=(ROOT/'src/EnemyStatePatternOpcode.cpp').read_text()
    control=(ROOT/'src/EnemyStateControlOpcode.cpp').read_text()
    dynamic=(ROOT/'src/EnemyStateDynamicParameterOpcode.cpp').read_text()
    management=(ROOT/'src/EnemyStateControllerManagementOpcode.cpp').read_text()
    time_source=(ROOT/'src/EnemyStateTimeOpcode.cpp').read_text()
    card_source=(ROOT/'src/EnemyStateCardOpcode.cpp').read_text()
    frontend_source=(ROOT/'src/EnemyStateFrontendOpcode.cpp').read_text()
    flags_clear=(ROOT/'src/EnemyStateAnimationFlagsClearOpcode.cpp').read_text()
    screen=(ROOT/'src/EnemyStateScreenOpcode.cpp').read_text()
    player_angle_source=(ROOT/'src/EnemyStatePlayerAngleOpcode.cpp').read_text()
    bullet_laser_cancel_source=(ROOT/'src/EnemyStateBulletLaserCancelOpcode.cpp').read_text()
    assert 'execute_enemy_bullet_laser_cancel_opcode(*this, opcode)' in root
    assert 'state.float_argument(0)' in bullet_laser_cancel_source
    assert 'state.context->bullet_controller()' in bullet_laser_cancel_source
    assert 'state.context->laser_controller()' in bullet_laser_cancel_source
    assert 'bullets->cancel_near(bullet_center, radius, 0)' in bullet_laser_cancel_source
    assert 'lasers->cancel_near(laser_center, radius, 0, 1)' in bullet_laser_cancel_source
    assert 'execute_enemy_player_angle_opcode(*this, opcode)' in root
    assert player_angle_source.count('state.context->player()->position_ref()') == 2
    assert 'scalar_math::arctangent(delta_y, delta_x)' in player_angle_source
    assert 'state.float_argument_destination(0)' in player_angle_source
    assert 'Player* Context::player()' in (ROOT/'src/Context.cpp').read_text()
    assert 'Context::player()' not in (ROOT/'src/DamageQueryProtocol.cpp').read_text()
    shared_queued_source=(ROOT/'src/EnemyStateSharedQueuedParametersOpcode.cpp').read_text()
    assert 'case 618:' in shared_queued_source
    assert 'state.float_argument(1)' in shared_queued_source
    assert 'state.float_argument(2)' in shared_queued_source
    assert 'polar(offset, direction, length)' in shared_queued_source
    assert 'record->vector_34.x = offset.x' in shared_queued_source
    assert 'record->vector_34.y = offset.y' in shared_queued_source
    assert 'case 620:' in shared_queued_source
    assert 'polar(offset, direction, length);' in shared_queued_source
    assert 'std::get<0>(std::move(selected))' in shared_queued_source
    assert 'std::get<1>(std::move(selected))' in shared_queued_source
    assert 'pair_first_address' not in shared_queued_source
    assert 'pair_second_address' not in shared_queued_source
    assert 'x < native_speed_override_threshold' in shared_queued_source
    assert 'entity->current_runtime->current()' in root
    assert 'execute_enemy_movement_opcode(*this, movement_opcode)' in root
    assert 'execute_enemy_pattern_opcode(*this, opcode)' in root
    assert 'execute_enemy_control_opcode(*this, opcode)' in root
    assert 'execute_enemy_dynamic_parameter_opcode(*this, opcode)' in root
    assert 'execute_enemy_controller_management_opcode(*this, opcode, controller_result)' in root
    assert 'execute_enemy_script_control_opcode(*this, instruction, opcode)' in root
    assert 'case 800:' in script_control and 'case 801:' in script_control and 'case 802:' in script_control
    assert 'target->terminate_async()' in script_control
    assert 'target->reset()' in script_control and 'target->select(script_name)' in script_control
    assert 'reinterpret_cast<const char*>(&instruction) + 0x18' in script_control
    assert 'target->position_ref().x' in script_control and 'target->position_ref().y' in script_control
    assert 'target->state_value().phases' in script_control
    assert 'target->terminate_async()' in script_control and 'target->select(target->state_value().phases' in script_control
    assert 'return source->select(this, name);' in ecl_manager_select
    assert 'execute_enemy_time_opcode(*this, opcode)' in root
    assert 'execute_enemy_card_opcode(*this, opcode)' in root
    assert 'execute_enemy_frontend_opcode(*this, opcode, frontend_result)' in root
    assert 'case 503:' in root and 'execute_enemy_animation_flags_clear_opcode(*this)' in root
    assert '& 0x3fffu' in flags_clear and 'state.flags.word_00 &= ~bits' in flags_clear
    assert '(state.flags.word_00 & 0x20u) == 0' in flags_clear
    assert 'set_animation_handle_flag0_recursively(&link.handle)' in flags_clear
    assert 'case 517:' in root and 'execute_enemy_screen_effect_spawn_opcode(*this)' in root
    assert 'integer_argument(2)' in screen and 'integer_argument(1)' in screen and 'integer_argument(0)' in screen
    assert 'screen_factory_4250f0(1, first, second, third, 0, 0, 0)' in screen
    assert 'if (opcode == 560 && entity->defeat())' in root
    case524=root[root.index('case 524:'):root.index('case 575:')]
    assert case524.index('integer_argument(0)') < case524.index('current_game_controller->set_field_34')
    assert case524.index('current_game_controller->set_field_34') < case524.index('field_280 = value') < case524.index('field_284 = 0')
    case575=root[root.index('case 575:'):root.index('default:',root.index('case 575:'))]
    assert case575.index('player(0)') < case575.index('integer_argument(0)') < case575.index('set_entity_flag_10')
    assert 'current_game_controller->set_field_34' in root
    assert 'receiver->set_entity_flag_10(value)' in root
    assert 'return 1;' in root
    assert 'return 0;' in root
    assert 'if (execute_enemy_laser_opcode(*this, opcode))' in root
    assert 'execute_enemy_animation_spawn_opcode(*this, opcode)' in root
    assert 'execute_enemy_fog_opcode(*this, opcode)' in root
    assert 'execute_enemy_membership_opcode(*this, opcode)' in root
    setter_source=(ROOT/'src/EnemyStateControllerSetterOpcode.cpp').read_text()
    root_test_source=(ROOT/'tests/enemy_state_dispatch_root.cpp').read_text()
    assert 'execute_enemy_controller_setter_opcode(EnemyState&' not in root_test_source
    assert 'void BulletController::set_vector_4c' not in root_test_source
    assert 'void EnemyController::set_field_88' not in root_test_source
    assert '::new (static_cast<void*>(bullet_controller_storage.data())) BulletController()' in root_test_source
    assert 'retarget_enemy_controller_during_integer_read' in root_test_source
    assert 'retarget_bullet_controller_during_first_float_read' in root_test_source
    assert 'retarget_context_player_during_first_float_read' in root_test_source
    assert 'expected_player_angle_617' in root_test_source
    assert 'player_angle_second_operand_threw' in root_test_source
    assert 'zero_vector_angle_617 == 0.0f' in root_test_source
    assert 'retarget_to_original_and_move_enemy_during_bullet_cancel' in root_test_source
    assert 'bullet_at_retargeted_center.state == 4' in root_test_source
    assert 'bullet_left_at_old_center.state == 1' in root_test_source
    assert 'laser_state_zero.circle_argument == 1' in root_test_source
    assert 'laser_wrong_context.circle_calls == 0' in root_test_source
    assert 'opcode616_radius_threw' in root_test_source
    assert 'src/BulletSpatialCancellation.cpp' in HOST_SOURCES
    assert 'src/BulletDistance.cpp' in HOST_SOURCES
    assert 'src/LaserCancelNear.cpp' in HOST_SOURCES
    assert 'src/LaserCancelCircleDefault.cpp' in HOST_SOURCES
    assert 'Player player_fixture;' in root_test_source
    assert 'Player alternate_player_fixture;' in root_test_source
    assert 'player_fixture.entity_flags.fields.bit_10 == 1' in root_test_source
    assert 'bool execute_enemy_shot_command_opcode(EnemyState&' not in root_test_source
    assert 'bool execute_enemy_shared_queued_parameters_opcode(EnemyState&' not in root_test_source
    assert 'std::numeric_limits<float>::quiet_NaN()' in root_test_source
    assert 'std::isnan(queued_record_620.vector_40.x)' in root_test_source
    assert 'queued_record_618.vector_34.z == 33.0f' in root_test_source
    assert 'queued_polar_second_float_threw' in root_test_source
    assert 'bool execute_enemy_laser_opcode(EnemyState&' not in root_test_source
    assert 'bool execute_enemy_mesh_opcode(EnemyState&' not in root_test_source
    assert 'execute_enemy_bullet_cancel_opcode' not in root_test_source
    assert 'animation_pool_resolve_calls == 1' in root_test_source
    assert 'dispatch_test_bullets->cancel_counter == cancel_counter_before_712 + 2' in root_test_source
    assert 'dialogue_cancel_bullet.state == 4' in root_test_source
    assert 'src/BulletCancellation.cpp' in HOST_SOURCES
    assert 'BulletController::cancel_all(std::int32_t)' not in root_test_source
    assert 'BulletController::active_list()' not in root_test_source
    assert 'mesh_owner_visible_during_float_read' in root_test_source
    assert 'render_mesh_ctor_arguments == std::array<std::int32_t,4>{17,17,0,9}' in root_test_source
    assert 'case 702:' in (ROOT/'src/EnemyStateLaserOpcode.cpp').read_text()
    assert 'case 713:' in (ROOT/'src/EnemyStateLaserOpcode.cpp').read_text()
    assert 'dispatch_laser_create_calls == 1' in root_test_source
    assert 'dispatch_laser_capture.receiver == dispatch_test_lasers_alternate' in root_test_source
    shot_command_source=(ROOT/'src/EnemyStateShotCommandOpcode.cpp').read_text()
    assert 'case 609:' in shot_command_source and 'case 612:' in shot_command_source
    assert 'state.writable_shot(static_cast<std::uint32_t>(record_index))' in shot_command_source
    assert 'metadata.commands.resize(required_size)' in shot_command_source
    assert 'metadata.field_30 = cursor_mode ? metadata.field_30 + 1u : required_size;' in shot_command_source
    assert 'run_shot_command_case(609' in root_test_source
    assert 'run_shot_command_case(610' in root_test_source
    assert 'run_shot_command_case(611' in root_test_source
    assert 'run_shot_command_case(612' in root_test_source
    assert 'shot_command_threw' in root_test_source
    case553=setter_source[setter_source.index('case 553:'):setter_source.index('case 554:')]
    assert case553.index('state.context->enemy_controller()') < case553.index('integer_argument(0)') < case553.index('set_field_88')
    case554=setter_source[setter_source.index('case 554:'):setter_source.index('default:')]
    assert case554.index('state.context->bullet_controller()') < case554.index('float_argument(1)') < case554.index('float_argument(0)') < case554.index('set_vector_4c')
    assert 'if (opcode != 555)' in (ROOT/'src/EnemyStateAnimationSpawnOpcode.cpp').read_text()
    fog_source=(ROOT/'src/EnemyStateFogOpcode.cpp').read_text()
    membership_source=(ROOT/'src/EnemyStateMembershipOpcode.cpp').read_text()
    assert 'if (opcode != 551)' in fog_source and 'float_argument(4)' in fog_source and 'float_argument(3)' in fog_source
    assert 'if (opcode != 549)' in membership_source and 'integer_argument(1)' in membership_source and 'integer_argument_destination(0)' in membership_source
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
        'execute_enemy_bullet_cancel_opcode',
    ):
        assert helper in root,helper
    pattern_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',pattern)]
    assert set(pattern_labels)=={506,507,508,509,510,556,567,568,572},pattern_labels
    assert 'session.field_70_is_two()' in pattern
    assert 'state.pattern.drop(origin, bomb_mark)' in pattern
    control_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',control)]
    assert set(control_labels)=={500,501,504,505,511,512,513,515,526,535,543,544,546,547,552,557,558,559,563,564,566},control_labels
    management_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',management)]
    assert set(management_labels)=={520,525,545,565,573},management_labels
    assert 'result = -1;' in management
    frontend_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',frontend_source)]
    assert set(frontend_labels)=={516,519,527,534,548},frontend_labels
    assert 'result = -1;' in frontend_source
    case527=frontend_source[frontend_source.index('case 527:'):frontend_source.index('case 534:')]
    assert case527.index('float_argument(1)') < case527.index('integer_argument(2)') < case527.index('state.health.field_04') < case527.index('integer_argument(0)') < case527.index('state.field_270') < case527.index('set_boss_gauge')
    case534=frontend_source[frontend_source.index('case 534:'):frontend_source.index('case 548:')]
    assert case534.index('integer_argument(0)') < case534.index('set_field_180')
    assert 'case 548:' in frontend_source and 'current_front->show_stage_title()' in frontend_source
    assert 'case 569:' in root and 'return 0;' in root[root.index('case 569:'):root.index('default:',root.index('case 569:'))]
    assert 'case 17: case 21: case 25: case 45: case 260: case 324:' in root
    selected_position_source=root[root.index('int execute_enemy_selected_position_opcode'):root.index('int EnemyState::execute_opcode')]
    assert selected_position_source.index('state.context->enemy_controller()') < selected_position_source.index('integer_argument(2)') < selected_position_source.index('controller->find(identifier)')
    assert selected_position_source.count('enemy->position_ref()')==2
    assert selected_position_source.count('state.position_ref()')==2
    assert selected_position_source.index('float_argument_destination(0)') < selected_position_source.index('float_argument_destination(1)')
    assert 'state.context->laser_controller()->reset_all_lasers()' in time_source
    assert 'case 552:' in control and '((value & 1u) << 3)' in control
    card_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',card_source)]
    assert set(card_labels)=={523,536,537,561,562},card_labels
    time_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',time_source)]
    assert set(time_labels)=={538,539,540,541,542,574},time_labels
    dynamic_labels=[int(x) for x in re.findall(r'\bcase\s+(\d+)\s*:',dynamic)]
    assert {529,530,570,571}.issubset(set(dynamic_labels)),dynamic_labels
    for source in (root,movement,pattern,control,dynamic,management,time_source,card_source,frontend_source,flags_clear,screen):
        for forbidden in ('__asm','__declspec(naked)','_emit','__nop'):
            assert forbidden not in source

    profile=['/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
             '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    for source,obj in (
        ('src/EnemyStateMovementOpcode.cpp','build/core209-canonical/EnemyStateMovementOpcode.obj'),
        ('src/EnemyStatePatternOpcode.cpp','build/core210-canonical/EnemyStatePatternOpcode.obj'),
        ('src/EnemyStateControlOpcode.cpp','build/core211-canonical/EnemyStateControlOpcode.obj'),
        ('src/EnemyStateDynamicParameterOpcode.cpp','build/core212-canonical/EnemyStateDynamicParameterOpcode.obj'),
        ('src/EnemyStateControllerManagementOpcode.cpp','build/core213-canonical/EnemyStateControllerManagementOpcode.obj'),
        ('src/EnemyStateTimeOpcode.cpp','build/core214-canonical/EnemyStateTimeOpcode.obj'),
        ('src/EnemyStateCardOpcode.cpp','build/core215-canonical/EnemyStateCardOpcode.obj'),
        ('src/EnemyStateFrontendOpcode.cpp','build/core216-canonical/EnemyStateFrontendOpcode.obj'),
        ('src/EnemyStateAnimationFlagsClearOpcode.cpp','build/core217-canonical/EnemyStateAnimationFlagsClearOpcode.obj'),
        ('src/EnemyStateScreenOpcode.cpp','build/core218-canonical/EnemyStateScreenOpcode.obj'),
        ('src/EnemyStateExecuteOpcode.cpp','build/core209-canonical/EnemyStateExecuteOpcode.obj'),
        ('src/EnemyStateControllerSetterOpcode.cpp','build/core213-canonical/EnemyStateControllerSetterOpcode.obj'),
        ('src/EnemyStateScriptControlOpcode.cpp','build/core220-canonical/EnemyStateScriptControlOpcode.obj'),
        ('src/EnemyStateShotCommandOpcode.cpp','build/core222-canonical/EnemyStateShotCommandOpcode.obj'),
        ('src/EnemyStateLaserOpcode.cpp','build/core223-canonical/EnemyStateLaserOpcode.obj'),
        ('src/EnemyStateMeshOpcode.cpp','build/core224-canonical/EnemyStateMeshOpcode.obj'),
        ('src/EnemyStateBulletCancelOpcode.cpp','build/core226-canonical/EnemyStateBulletCancelOpcode.obj'),
        ('src/EnemyStateQueueCopyOpcode.cpp','build/core225-canonical/EnemyStateQueueCopyOpcode.obj'),
        ('src/EnemyStateSharedQueuedParametersOpcode.cpp','build/gpt-web-enemy-620-canonical/EnemyStateSharedQueuedParametersOpcode.obj'),
        ('src/Player.cpp','build/core208-canonical/Player.obj'),
        ('src/PlayerStorage.cpp','build/core208-canonical/PlayerStorage.obj'),
        ('src/EnemyStatePlayerAngleOpcode.cpp','build/gpt-web-enemy-617-canonical/EnemyStatePlayerAngleOpcode.obj'),
        ('src/EnemyStateBulletLaserCancelOpcode.cpp','build/gpt-web-enemy-616-canonical/EnemyStateBulletLaserCancelOpcode.obj'),
        ('src/BulletSpatialCancellation.cpp','build/gpt-web-enemy-616-canonical/BulletSpatialCancellation.obj'),
        ('src/BulletDistance.cpp','build/gpt-web-enemy-616-canonical/BulletDistance.obj'),
        ('src/LaserCancelNear.cpp','build/gpt-web-enemy-616-canonical/LaserCancelNear.obj'),
        ('src/LaserBase.cpp','build/gpt-web-enemy-616-canonical/LaserBase.obj'),
        ('src/LaserCancelCircleDefault.cpp','build/gpt-web-enemy-616-canonical/LaserCancelCircleDefault.obj'),
        ('src/PlayerDirection.cpp','build/core208-canonical/PlayerDirection.obj'),
        ('src/EclManagerSelect.cpp','build/core219-canonical/EclManagerSelect.obj'),
        ('src/EnemyStateAccessor.cpp','build/core221-canonical/EnemyStateAccessor.obj'),
        ('src/Bullet.cpp','build/core174-canonical/Bullet.obj'),
        ('src/BulletController.cpp','build/core203-canonical/BulletController.obj'),
        ('src/BulletValues.cpp','build/core141-canonical/BulletValues.obj'),
        ('src/BulletCancellation.cpp','build/core226-canonical/BulletCancellation.obj'),
        ('src/EnemyData.cpp','build/core178-canonical/EnemyData.obj'),
        ('src/Context.cpp','build/core163-canonical/Context.obj'),
        ('src/DamageQueryProtocol.cpp','build/core209-canonical/DamageQueryProtocol.obj'),
        ('src/Rectangle.cpp','build/core163-canonical/Rectangle.obj'),
        ('src/FrontInfDialogueCommand626.cpp','build/gpt-web-dialogue-canonical/FrontInfDialogueCommand626.obj'),
        ('src/FrontDialogueVoiceSound104.cpp','build/gpt-web-dialogue-canonical/FrontDialogueVoiceSound104.obj'),
        ('src/FrontDialogueRelease97.cpp','build/gpt-web-dialogue-canonical/FrontDialogueRelease97.obj'),
        ('src/FrontDialogueFieldViews.cpp','build/gpt-web-dialogue-canonical/FrontDialogueFieldViews.obj'),
        ('src/FrontDialogueAllocate156.cpp','build/gpt-web-dialogue-canonical/FrontDialogueAllocate156.obj'),
        ('src/EnemyStateDialogueOpcode.cpp','build/gpt-web-dialogue-canonical/EnemyStateDialogueOpcode.obj'),
        ('src/SoundInfEnqueue323.cpp','build/gpt-web-sound-canonical/SoundInfEnqueue323.obj'),
        ('src/NativeSoundCommandArrayView.cpp','build/gpt-web-sound-canonical/NativeSoundCommandArrayView.obj'),
    ):
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),source,obj,*profile],cwd=ROOT,check=True)

    queue_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-queue-copy-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original opcode 614: 572B / 129 x86 / 19 direct E8' in queue_source_audit.stdout
    print(queue_source_audit.stdout,end='')

    bullet_cancel_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-bullet-cancel-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy opcode 712: selector 164, 196B / 42 x86 / 9 ordered E8' in bullet_cancel_source_audit.stdout
    print(bullet_cancel_source_audit.stdout,end='')

    bullet_laser_cancel_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-bullet-laser-cancel-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy opcode 616: selector 134, 175B / 37 x86 / 7 ordered E8 calls' in bullet_laser_cancel_source_audit.stdout
    print(bullet_laser_cancel_source_audit.stdout,end='')

    player_angle_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-player-angle-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy opcode 617: selector 135, 203B / 41 x86 / 8 ordered E8 calls' in player_angle_source_audit.stdout
    print(player_angle_source_audit.stdout,end='')

    shared_polar_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-shared-queued-polar-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy opcode 618: selector 136, 243B / 55 x86 / 10 ordered direct E8 calls' in shared_polar_source_audit.stdout
    print(shared_polar_source_audit.stdout,end='')

    shared_queued_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-shared-queued-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy opcode 620: 250B / 57 x86 / 8 ordered direct E8 calls' in shared_queued_source_audit.stdout
    assert 'PASS COMISS/JBE unordered NaN behavior' in shared_queued_source_audit.stdout
    print(shared_queued_source_audit.stdout,end='')

    bullet_laser_cancel_object=ROOT/'build/gpt-web-enemy-616-canonical/EnemyStateBulletLaserCancelOpcode.obj'
    bullet_laser_cancel_dump=subprocess.run(
        ['objdump','-dr',str(bullet_laser_cancel_object)],cwd=ROOT,check=True,text=True,capture_output=True).stdout
    bullet_laser_cancel_marker='<?execute_enemy_bullet_laser_cancel_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert bullet_laser_cancel_marker in bullet_laser_cancel_dump
    bullet_laser_cancel_function=bullet_laser_cancel_dump.split(bullet_laser_cancel_marker,1)[1].split('Disassembly of section',1)[0]
    bullet_laser_cancel_calls=re.findall(r'DISP32\s+([^\r\n]+)',bullet_laser_cancel_function)
    expected_bullet_laser_cancel_calls=[
        '?float_argument@EnemyState@th20@@QAEMH@Z',
        '?bullet_controller@Context@th20@@QAEPAUBulletController@2@XZ',
        '?position_ref@EnemyState@th20@@QAEAAUVector3@2@XZ',
        '?cancel_near@BulletController@th20@@QAEHABUVector3@2@MH@Z',
        '?laser_controller@Context@th20@@QAEPAVLaserController@2@XZ',
        '?position_ref@EnemyState@th20@@QAEAAUVector3@2@XZ',
        '?cancel_near@LaserController@th20@@QAEHABUVector3@2@MHH@Z',
    ]
    assert len(bullet_laser_cancel_calls)==len(expected_bullet_laser_cancel_calls),(bullet_laser_cancel_calls,expected_bullet_laser_cancel_calls)
    for actual,expected in zip(bullet_laser_cancel_calls,expected_bullet_laser_cancel_calls):
        assert expected in actual,(actual,expected)
    print('PASS natural C++ opcode-616 COFF: radius, Bullet Context/position/Boss, then independent Laser Context/position/Boss')

    player_angle_object=ROOT/'build/gpt-web-enemy-617-canonical/EnemyStatePlayerAngleOpcode.obj'
    player_angle_dump=subprocess.run(
        ['objdump','-dr',str(player_angle_object)],cwd=ROOT,check=True,text=True,capture_output=True).stdout
    player_angle_marker='<?execute_enemy_player_angle_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert player_angle_marker in player_angle_dump
    player_angle_function=player_angle_dump.split(player_angle_marker,1)[1].split('Disassembly of section',1)[0]
    player_angle_calls=re.findall(r'DISP32\s+([^\r\n]+)',player_angle_function)
    expected_player_angle_calls=[
        '?player@Context@th20@@QAEPAVPlayer@2@XZ',
        '?position_ref@Player@th20@@QAEAAUVector3@2@XZ',
        '?float_argument@EnemyState@th20@@QAEMH@Z',
        '?player@Context@th20@@QAEPAVPlayer@2@XZ',
        '?position_ref@Player@th20@@QAEAAUVector3@2@XZ',
        '?float_argument@EnemyState@th20@@QAEMH@Z',
        '?arctangent@scalar_math@th20@@YAMMM@Z',
        '?float_argument_destination@EnemyState@th20@@QAEPAMH@Z',
    ]
    assert len(player_angle_calls)==len(expected_player_angle_calls),(player_angle_calls,expected_player_angle_calls)
    for actual,expected in zip(player_angle_calls,expected_player_angle_calls):
        assert expected in actual,(actual,expected)
    context_object=ROOT/'build/core163-canonical/Context.obj'
    context_dump=subprocess.run(['objdump','-dr',str(context_object)],cwd=ROOT,check=True,text=True,capture_output=True).stdout
    context_player_marker='<?player@Context@th20@@QAEPAVPlayer@2@XZ>:'
    assert context_player_marker in context_dump
    context_player_function=context_dump.split(context_player_marker,1)[1].split('Disassembly of section',1)[0]
    assert '0x4(' in context_player_function
    player_direction_object=ROOT/'build/core208-canonical/PlayerDirection.obj'
    player_direction_dump=subprocess.run(['objdump','-dr',str(player_direction_object)],cwd=ROOT,check=True,text=True,capture_output=True).stdout
    position_ref_marker='<?position_ref@Player@th20@@QAEAAUVector3@2@XZ>:'
    assert position_ref_marker in player_direction_dump
    position_ref_function=player_direction_dump.split(position_ref_marker,1)[1].split('Disassembly of section',1)[0]
    assert '0x614' in position_ref_function
    print('PASS natural C++ opcode-617 COFF: two Context::player/Player::position_ref reads, ordered VM operands, atan2 and destination writeback')

    shared_queued_object=ROOT/'build/gpt-web-enemy-620-canonical/EnemyStateSharedQueuedParametersOpcode.obj'
    shared_queued_dump=subprocess.run(
        ['objdump','-dr',str(shared_queued_object)],cwd=ROOT,check=True,text=True,capture_output=True).stdout
    shared_queued_marker='<?execute_enemy_shared_queued_parameters_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert shared_queued_marker in shared_queued_dump
    shared_queued_function=shared_queued_dump.split(shared_queued_marker,1)[1]
    shared_queued_calls=re.findall(r'DISP32\s+([^\r\n]+)',shared_queued_function)
    get0_indices=[i for i,call in enumerate(shared_queued_calls) if '??$get@$0A@PAUEnemyQueuedRecord' in call]
    polar_get0_index=next(i for i in get0_indices if 'float_argument@EnemyState@th20' in shared_queued_calls[i-3] and 'float_argument@EnemyState@th20' in shared_queued_calls[i-2] and 'shared_shot@EnemyState@th20' in shared_queued_calls[i-1])
    assert 'integer_argument@EnemyState@th20' in shared_queued_calls[polar_get0_index-4]
    assert '??$get@$00PAUEnemyQueuedRecord' in shared_queued_calls[polar_get0_index+1]
    assert '??0Vector3@th20@@QAE@XZ' in shared_queued_calls[polar_get0_index+2]
    assert 'polar@th20@@YAXAAUVector3@1@MM@Z' in shared_queued_calls[polar_get0_index+3]
    get0_index=next(i for i in get0_indices if 'integer_argument@EnemyState@th20' in shared_queued_calls[i-2] and 'shared_shot@EnemyState@th20' in shared_queued_calls[i-1])
    assert '??$get@$00PAUEnemyQueuedRecord' in shared_queued_calls[get0_index+1]
    assert 'float_argument@EnemyState@th20' in shared_queued_calls[get0_index+2]
    assert 'float_argument@EnemyState@th20' in shared_queued_calls[get0_index+3]
    assert 'comiss' in shared_queued_function and 'jbe' in shared_queued_function
    assert '?native_speed_override_threshold@th20@@3MB' in shared_queued_function
    assert '?native_one_56c8cc@th20@@3MB' in shared_queued_function
    assert '0x34(' in shared_queued_function and '0x38(' in shared_queued_function
    assert '0x40(' in shared_queued_function and '0x44(' in shared_queued_function and '0x48(' in shared_queued_function
    assert 'pair_first_address' not in shared_queued_dump and 'pair_second_address' not in shared_queued_dump
    print('PASS natural C++ opcode-618/620 COFF: ordered shared_shot/std::get, Vector3/polar, COMISS/JBE and direct XY/XYZ stores')

    mesh_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-mesh-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy opcode 621: 346B / 70 x86 / 7 E8' in mesh_source_audit.stdout
    print(mesh_source_audit.stdout,end='')

    laser_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-laser-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    laser_case_counts=((702,682,153,15),(703,787,176,16),(711,619,141,15),(713,611,137,16))
    for opcode,byte_count,heads,calls in laser_case_counts:
        assert f'PASS original opcode {opcode}: {heads} CFG heads, {calls} E8' in laser_source_audit.stdout
    assert sum(row[1] for row in laser_case_counts)==2699
    assert sum(row[2] for row in laser_case_counts)==607
    assert sum(row[3] for row in laser_case_counts)==62
    print(laser_source_audit.stdout,end='')
    print('PASS native Laser case family totals: 2699B / 607 instruction heads / 62 E8 calls')

    shot_source_audit=subprocess.run(
        [str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-enemy-shot-command-opcode-source.py')],
        cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS original Enemy shared opcode head 0x4931DD: 1457B / 314 x86 / 29 E8' in shot_source_audit.stdout
    print(shot_source_audit.stdout,end='')
    print('PASS locked PE 609/610/611/612 selector index 130, 1457B/314-instruction extent and ordered 29 E8 call map')

    # The 614 helper must preserve both VM reads before either mutation,
    # destination growth before source growth, independent iterator advances,
    # and the final typed EnemyQueuedRecord assignment.
    queue_object=ROOT/'build/core225-canonical/EnemyStateQueueCopyOpcode.obj'
    queue_dump=subprocess.run(['objdump','-dr',str(queue_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    queue_marker='<?execute_enemy_queue_copy_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert queue_marker in queue_dump
    queue_function=queue_dump.split(queue_marker,1)[1].split('Disassembly of section',1)[0]
    queue_calls=re.findall(r'DISP32\s+([^\r\n]+)',queue_function)
    assert len(queue_calls)==24,queue_calls
    semantic_queue_calls=[
        '?integer_argument@EnemyState@th20',
        '?integer_argument@EnemyState@th20',
        '?end@?$forward_list@UEnemyQueuedRecord@th20',
        '?begin@?$forward_list@UEnemyQueuedRecord@th20',
        '??$distance@',
        '?resize@?$forward_list@UEnemyQueuedRecord@th20',
        '?end@?$forward_list@UEnemyQueuedRecord@th20',
        '?begin@?$forward_list@UEnemyQueuedRecord@th20',
        '??$distance@',
        '?resize@?$forward_list@UEnemyQueuedRecord@th20',
        '?begin@?$forward_list@UEnemyQueuedRecord@th20',
        '??$advance@',
        '?begin@?$forward_list@UEnemyQueuedRecord@th20',
        '??$advance@',
        '??D?$_Flist_iterator',
        '??D?$_Flist_iterator',
        '??4EnemyQueuedRecord@th20',
        '@__security_check_cookie@4',
    ]
    # Ignore only the compiler's explicit local-iterator zero-init helpers.
    semantic=[call for call in queue_calls if '__autoclassinit2@?$_Flist_iterator' not in call]
    assert len(semantic)==len(semantic_queue_calls),(semantic,queue_calls)
    for actual,expected in zip(semantic,semantic_queue_calls):
        assert expected in actual,(actual,expected)
    assert 'src/EnemyStateQueueCopyOpcode.cpp' in HOST_SOURCES
    assert 'src/EnemyQueuedRecordAssignment.cpp' in HOST_SOURCES
    assert 'bool execute_enemy_queue_copy_opcode(EnemyState&' not in root_test_source
    print('PASS natural C++ Enemy queue-copy 614 COFF helper preserves both operand reads, destination/source resize order, independent advances and typed record assignment')

    bullet_cancel_object=ROOT/'build/core226-canonical/EnemyStateBulletCancelOpcode.obj'
    bullet_cancel_dump=subprocess.run(['objdump','-dr',str(bullet_cancel_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    bullet_cancel_marker='<?execute_enemy_bullet_cancel_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert bullet_cancel_marker in bullet_cancel_dump
    bullet_cancel_function=bullet_cancel_dump.split(bullet_cancel_marker,1)[1].split('Disassembly of section',1)[0]
    bullet_cancel_calls=re.findall(r'DISP32\s+([^\r\n]+)',bullet_cancel_function)
    expected_bullet_cancel_calls=[
        '??0Vector3@th20',
        '?float_argument@EnemyState@th20',
        '?float_argument@EnemyState@th20',
        '??A?$vector@UEnemyAnimationLink@th20',
        '?resolve@AnimationHandle@th20',
        '?bullet_controller@Context@th20',
        '?rotation_z_value@Animation@th20',
        '?position_ref@EnemyState@th20',
        '?cancel_in_rectangle@BulletController@th20',
        '@__security_check_cookie@4',
    ]
    assert len(bullet_cancel_calls)==len(expected_bullet_cancel_calls),bullet_cancel_calls
    for actual,expected in zip(bullet_cancel_calls,expected_bullet_cancel_calls):
        assert expected in actual,(actual,expected)
    assert 'src/BulletRectangleCancellation.cpp' in HOST_SOURCES
    assert 'src/RectangleCollisions.cpp' in HOST_SOURCES
    assert 'src/BulletCollisionHandle.cpp' in HOST_SOURCES
    assert 'src/AnimationGeometry.cpp' in HOST_SOURCES
    print('PASS natural C++ Enemy opcode 712 COFF helper preserves all nine ordered Vector3/VM/animation/Context/position/707B cancel relocations')

    # The 621 helper must retain native owner release, owner allocation,
    # float-before-integer reads, both Angle stores and conditional RenderMesh
    # allocation in the natural C++ COFF object.
    mesh_object=ROOT/'build/core224-canonical/EnemyStateMeshOpcode.obj'
    mesh_dump=subprocess.run(['objdump','-dr',str(mesh_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    mesh_marker='<?execute_enemy_mesh_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert mesh_marker in mesh_dump
    mesh_function=mesh_dump.split(mesh_marker,1)[1].split('Disassembly of section',1)[0]
    mesh_calls=re.findall(r'DISP32\s+([^\r\n]+)',mesh_function)
    expected_mesh_calls=[
        '??$release_object@UEnemyMeshOwner@th20',
        '??$allocate_object@UEnemyMeshOwner@th20',
        '?float_argument@EnemyState@th20',
        '?integer_argument@EnemyState@th20',
        '??4Angle@th20',
        '??4Angle@th20',
        '??$allocate_object@VRenderMesh@th20@@HHHH@DiagnosticAllocator@th20',
    ]
    assert len(mesh_calls)==len(expected_mesh_calls),mesh_calls
    for actual,expected in zip(mesh_calls,expected_mesh_calls):
        assert expected in actual,(actual,expected)
    assert 'src/EnemyStateMeshOpcode.cpp' in HOST_SOURCES
    assert 'src/EnemyMesh.cpp' in HOST_SOURCES
    assert 'animation_spawn_flags == 0u' in root_test_source
    assert 'src/MeshResourceAccess.cpp' in HOST_SOURCES
    print('PASS natural C++ Enemy mesh 621 COFF helper preserves all seven ordered allocator/operand/Angle/RenderMesh relocations')

    # Verify the full natural-C++ Laser helper call sequence, including each
    # real parameter constructor/destructor, writable-shot COW selection,
    # PMR command copy, late handle reads, Context lookup and factory handoff.
    laser_object=ROOT/'build/core223-canonical/EnemyStateLaserOpcode.obj'
    laser_dump=subprocess.run(['objdump','-dr',str(laser_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    laser_marker='00000000 <?execute_enemy_laser_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert laser_marker in laser_dump
    laser_function=laser_dump.split(laser_marker,1)[1].split('Disassembly of section',1)[0]
    laser_calls=re.findall(r'DISP32\s+([^\r\n]+)',laser_function)
    expected_laser_calls=[
        '??0LaserType0Parameters@th20',
        '?integer_argument@EnemyState@th20',
        '?writable_shot@EnemyState@th20',
        '??4?$vector@UBulletCommand@th20',
        '??HVector3@th20',
        '?position_ref@EnemyState@th20',
        '??HVector3@th20',
        '?normalize_angle@th20',
        '?laser_controller@Context@th20',
        '?create_laser@LaserController@th20',
        '??1LaserType0Parameters@th20',
        '??0LaserType1Parameters@th20',
        '?integer_argument@EnemyState@th20',
        '?writable_shot@EnemyState@th20',
        '??4?$vector@UBulletCommand@th20',
        '??HVector3@th20',
        '?position_ref@EnemyState@th20',
        '??HVector3@th20',
        '?normalize_angle@th20',
        '?integer_argument@EnemyState@th20',
        '?laser_controller@Context@th20',
        '?create_laser@LaserController@th20',
        '??1LaserType1Parameters@th20',
        '??0LaserType2Parameters@th20',
        '?integer_argument@EnemyState@th20',
        '?writable_shot@EnemyState@th20',
        '??4?$vector@UBulletCommand@th20',
        '??HVector3@th20',
        '?position_ref@EnemyState@th20',
        '??HVector3@th20',
        '?normalize_angle@th20',
        '?laser_controller@Context@th20',
        '?create_laser@LaserController@th20',
        '??1LaserType2Parameters@th20',
        '??0LaserType3Parameters@th20',
        '?integer_argument@EnemyState@th20',
        '?writable_shot@EnemyState@th20',
        '??4?$vector@UBulletCommand@th20',
        '??HVector3@th20',
        '?position_ref@EnemyState@th20',
        '??HVector3@th20',
        '?normalize_angle@th20',
        '?integer_argument@EnemyState@th20',
        '?laser_controller@Context@th20',
        '?create_laser@LaserController@th20',
        '??1LaserType3Parameters@th20',
        '@__security_check_cookie@4',
    ]
    assert len(laser_calls)==len(expected_laser_calls),laser_calls
    for actual,expected in zip(laser_calls,expected_laser_calls):
        assert expected in actual,(actual,expected)
    assert 'src/EnemyStateLaserOpcode.cpp' in HOST_SOURCES
    assert 'src/LaserParameters.cpp' in HOST_SOURCES
    print('PASS natural C++ Laser 702/703/711/713 COFF helper preserves all 47 ordered constructor/selector/vector/position/normalize/Context/factory relocations')

    # The native 324 case calls each selected/fallback position getter twice,
    # with a destination lookup after each component. Verify the natural C++
    # object retains the same eleven ordered calls instead of caching a Vector3.
    root_object=ROOT/'build/core209-canonical/EnemyStateExecuteOpcode.obj'
    object_dump=subprocess.run(['objdump','-dr',str(root_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    marker='<?execute_enemy_selected_position_opcode@th20@@YAHAAUEnemyState@1@@Z>:'
    assert marker in object_dump
    object_function=object_dump.split(marker,1)[1].split('Disassembly of section',1)[0]
    object_calls=re.findall(r'DISP32\s+([^\r\n]+)',object_function)
    expected_object_calls=[
        '?enemy_controller@Context@th20',
        '?integer_argument@EnemyState@th20',
        '?find@EnemyController@th20',
        '?position_ref@Enemy@th20',
        '?float_argument_destination@EnemyState@th20',
        '?position_ref@Enemy@th20',
        '?float_argument_destination@EnemyState@th20',
        '?position_ref@EnemyState@th20',
        '?float_argument_destination@EnemyState@th20',
        '?position_ref@EnemyState@th20',
        '?float_argument_destination@EnemyState@th20',
    ]
    assert len(object_calls)==len(expected_object_calls),object_calls
    for actual,expected in zip(object_calls,expected_object_calls):
        assert expected in actual,(actual,expected)

    # Both controller-setter cases must retain the native call order in the
    # compiled natural-C++ helper, not merely in its source spelling.
    script_control_object=ROOT/'build/core220-canonical/EnemyStateScriptControlOpcode.obj'
    script_control_dump=subprocess.run(['objdump','-dr',str(script_control_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    script_control_marker='<?execute_enemy_script_control_opcode@th20@@YA_NAAUEnemyState@1@ABUEclInstruction@1@H@Z>:'
    assert script_control_marker in script_control_dump
    script_control_function=script_control_dump.split(script_control_marker,1)[1].split('Disassembly of section',1)[0]
    script_control_calls=re.findall(r'DISP32\s+([^\r\n]+)',script_control_function)
    expected_script_control_calls=[
        '?enemy_controller@Context@th20',
        '?integer_argument@EnemyState@th20',
        '?find@EnemyController@th20',
        '?terminate_async@EclManager@th20',
        '?reset@EclManager@th20',
        '?select@EclManager@th20',
        '?enemy_controller@Context@th20',
        '?integer_argument@EnemyState@th20',
        '?find@EnemyController@th20',
        '?position_ref@Enemy@th20',
        '?float_argument_destination@EnemyState@th20',
        '?position_ref@Enemy@th20',
        '?float_argument_destination@EnemyState@th20',
        '?integer_argument@EnemyState@th20',
        '?enemy_controller@Context@th20',
        '?selected@EnemyController@th20',
        '?state_value@Enemy@th20',
        '??A?$vector@UEnemyPhase@th20',
        '?state_value@Enemy@th20',
        '??A?$vector@UEnemyPhase@th20',
        '?terminate_async@EclManager@th20',
        '?reset@EclManager@th20',
        '?state_value@Enemy@th20',
        '??A?$vector@UEnemyPhase@th20',
        '?select@EclManager@th20',
    ]
    assert len(script_control_calls)==len(expected_script_control_calls),script_control_calls
    for actual,expected in zip(script_control_calls,expected_script_control_calls):
        assert expected in actual,(actual,expected)

    # Enemy::state_value is the second natural owner view of the same
    # relocation-free +0x88 getter already strictly represented by
    # Session::player_table. The physical 19B head is credited only once.
    accessor_object=ROOT/'build/core221-canonical/EnemyStateAccessor.obj'
    accessor_bytes_dump=subprocess.run(['objdump','-s','-j','.text$mn',str(accessor_object)],
        cwd=ROOT,check=True,text=True,capture_output=True).stdout
    accessor_words=[]
    for line in accessor_bytes_dump.splitlines():
        fields=line.split()
        if len(fields) >= 2 and re.fullmatch(r'[0-9a-f]{4}',fields[0]):
            for field in fields[1:]:
                if re.fullmatch(r'(?:[0-9a-f]{2}){1,4}',field):
                    accessor_words.append(field)
                else:
                    break
    accessor_hex=''.join(accessor_words)
    assert bytes.fromhex(accessor_hex) == pe.get_data(0x004989F0-image_base,19)

    shot_command_object=ROOT/'build/core222-canonical/EnemyStateShotCommandOpcode.obj'
    shot_command_dump=subprocess.run(['objdump','-dr',str(shot_command_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    shot_command_marker='<?execute_enemy_shot_command_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert shot_command_marker in shot_command_dump
    shot_command_function=shot_command_dump.split(shot_command_marker,1)[1].split('Disassembly of section',1)[0]
    shot_command_calls=re.findall(r'DISP32\s+([^\r\n]+)',shot_command_function)
    expected_shot_command_calls=[
        '?integer_argument@EnemyState@th20',
        '?writable_shot@EnemyState@th20',
        '?integer_argument@EnemyState@th20',
        '?size@?$vector@UBulletCommand@th20',
        '?resize@?$vector@UBulletCommand@th20',
        '?integer_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?integer_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?integer_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?integer_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?integer_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?integer_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?float_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?float_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?float_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '?float_argument@EnemyState@th20',
        '??A?$vector@UBulletCommand@th20',
        '@__security_check_cookie@4',
    ]
    assert len(shot_command_calls)==len(expected_shot_command_calls),shot_command_calls
    for actual,expected in zip(shot_command_calls,expected_shot_command_calls):
        assert expected in actual,(actual,expected)

    setter_object=ROOT/'build/core213-canonical/EnemyStateControllerSetterOpcode.obj'
    setter_dump=subprocess.run(['objdump','-dr',str(setter_object)],cwd=ROOT,
        check=True,text=True,capture_output=True).stdout
    setter_marker='<?execute_enemy_controller_setter_opcode@th20@@YA_NAAUEnemyState@1@H@Z>:'
    assert setter_marker in setter_dump
    setter_function=setter_dump.split(setter_marker,1)[1].split('Disassembly of section',1)[0]
    setter_calls=re.findall(r'DISP32\s+([^\r\n]+)',setter_function)
    expected_setter_calls=[
        '?enemy_controller@Context@th20',
        '?integer_argument@EnemyState@th20',
        '?set_field_88@EnemyController@th20',
        '?bullet_controller@Context@th20',
        '?float_argument@EnemyState@th20',
        '?float_argument@EnemyState@th20',
        '?set_vector_4c@BulletController@th20',
    ]
    assert len(setter_calls)==len(expected_setter_calls),setter_calls
    for actual,expected in zip(setter_calls,expected_setter_calls):
        assert expected in actual,(actual,expected)

    host=ROOT/'build/core209-enemy-dispatch-root-test'
    command=['g++-13','-std=c++20','-O1','-Wall','-Wextra','-Werror','-Wno-class-memaccess',
        '-D__fastcall=','-D__cdecl=','-D__thiscall=',
        '-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-pthread','-Isrc',
        '-fsanitize=address,undefined','-fno-sanitize-recover=all','-fno-sanitize=vptr',
        *HOST_SOURCES,'-o',str(host)]
    subprocess.run(command,cwd=ROOT,check=True)
    result=subprocess.run([str(host)],cwd=ROOT,check=True,text=True,capture_output=True)
    assert 'PASS root dispatch: Enemy bullet rectangle cancel 712 (real AnimationHandle resolve/rotation and 707B BulletController cancel boss), Enemy queue copy 614 (full typed record assignment, shared metadata ownership, destination/source PMR growth and second-operand exception order), Enemy bullet plus Laser radial cancel 616 (real 320B BulletController and 288B LaserController cancel_near Bosses, live Context/position retargeting), Enemy player angle 617 (two live Context/Player position reads, atan2 and VM destination writeback), Enemy shared queued polar 618 (operand order, ensure-only record, polar Vector3 XY transform and Z preservation), Enemy shared queued parameters 620 (ensure-only shared record, std::pair extraction, ordered X/Y writes and NaN-compatible threshold), Enemy mesh 621 (real allocator/owner release, positive-radius RenderMesh factory and operand-failure order), Laser 702/703/711/713 (real parameter temporaries, writable-shot COW and late Context selection), shot commands 609/610/611/612 (real writable-shot COW and PMR command vector), script select 800, selected position writeback 801, phase-selected script restarts 802, movement 400/404/424/448, animation flags 502/503, ScreenInf opcode 517 and dialogue cleanup 518 (real Bullet cancel-all traversal), global-owner opcodes 524/575, front gauge/title 527/534/548, selected-Enemy position 324, laser reset 539, bit flag 552, membership 549, fog 551, controller setters 553/554, animation/sound 555, reserved opcode 569, pattern 506-510/556/567/568/572, bounds/health/controller/state 500-559/563/564/566, controller selection/clear 520/525/545/565/573, timer/mode/time 538/539/540/541/542/574, card/health 523/536/537/561/562, sound queue enqueue plus dialogue 516/518/519, dynamic parameter copies 529/530/570/571 and special 560 return' in result.stdout
    print(result.stdout,end='')
    print(f'PASS maintained root host executes {len(HOST_SOURCES)} focused source units under ASan/UBSan')
    print('PASS immutable native EnemyState::execute_opcode root: 41,967B and SHA-256')
    print('PASS original compressed dispatch pointers and bounded E8 call maps for all nine EnemyPattern cases')
    print('PASS original compressed dispatch pointers and ordered E8 maps for all 21 bounds/health/controller/state cases (1,824B/373 heads/52 calls)')
    print('PASS original compressed dispatch pointers and ordered E8 maps for animation flag cases 502/503 (2,944B/592 instructions/8 calls)')
    print('PASS original compressed dispatch pointer and ordered E8 map for ScreenInf opcode 517 (99B/25 instructions/4 calls)')
    print('PASS original compressed dispatch pointers and ordered E8 maps for controller selection/clear 520/525/545/565/573 (289B/65 heads/17 calls)')
    print('PASS original compressed dispatch pointers and ordered E8 maps for timer/mode/time 538/539/540/541/542/574 (624B/130 heads/16 calls)')
    print('PASS original compressed dispatch pointers and ordered E8 maps for card/health 523/536/537/561/562 (235B/52 heads/11 calls)')
    print('PASS original compressed dispatch pointers and ordered E8 maps for front sound/gauge/title 516/519/527/534/548 (351B/78 heads/14 calls)')
    print('PASS original compressed dispatch pointer and ordered E8 map for selected-Enemy position opcode 324 (276B/53 instructions/11 calls)')
    print('PASS natural C++ opcode-324 COFF object retains all eleven ordered calls and repeated XY position reads')
    print('PASS natural C++ 553/554 COFF helper retains all seven ordered Context/VM/setter calls')
    print('PASS natural C++ 800/801 COFF helper retains all thirteen ordered Context/VM/Enemy/EclManager calls')
    print('PASS native Enemy opcode 800/801/802 selector, instruction and 25-call natural-source order')
    print('PASS production Enemy queue-copy opcode 614 helper and exact EnemyQueuedRecord assignment linked into ASan/UBSan root host')
    print('PASS production Enemy shared queued polar opcode 618 helper linked into ASan/UBSan root host with argument-order and vector-lane preservation tests')
    print('PASS production Enemy shared queued-parameter opcode 620 helper linked into ASan/UBSan root host with ensure-only shared metadata and native NaN threshold semantics')
    print('PASS production Enemy bullet rectangle cancel opcode 712 helper linked into ASan/UBSan root host with real AnimationHandle/rotation and 707B BulletController cancellation boss')
    print('PASS production 242B BulletController::cancel_all and 19B active_list linked into ASan/UBSan root host; opcode 518 cancels a live active Bullet through the real iterator traversal')
    print('PASS production Enemy mesh opcode 621 helper linked into ASan/UBSan root host with real EnemyMeshOwner allocation/release and conditional RenderMesh allocation')
    print('PASS production Enemy Laser 702/703/711/713 helper linked into ASan/UBSan root host with real parameter temporaries and capture-only factory boundary')
    print('PASS production Enemy shot-command 609/610/611/612 helper linked into ASan/UBSan root host with real writable-shot selector and PMR vector')
    print('PASS natural C++ shot-command COFF helper preserves 25 ordered semantic relocations and ten distinct PMR vector element accesses')
    print('PASS Enemy::state_value natural C++ alias strictly matches the shared original 19B +0x88 getter without duplicate byte credit')
    print('PASS original opcode-549 membership (95B), opcode-551 fog (257B), opcode-553/554 controller setters (66B/106B) and opcode-555 animation/sound Boss (388B) selector/call maps')
    print('PASS original opcode-569 selector index 173 points directly to the verified common return-zero epilogue')
    print('PASS original compressed dispatch pointers and ordered E8 maps for global-owner opcodes 524/575 (135B/31 heads/5 calls)')
    print('PASS original compressed dispatch pointers and ordered E8 maps for dynamic parameter copies 529/530/570/571 (1,262B/268 heads/48 calls)')
    print('PASS 49 movement cases, nine EnemyPattern cases, 21 control/state cases, five controller selection/clear cases, six timer/mode/time cases, five card/health cases, five front sound/gauge/title cases, five restored membership/fog/controller/animation cases, two global-owner cases, one reserved epilogue case, four dynamic parameter cases, opcode 614 queue copy, four shot-command variants, four Laser variants, Enemy mesh lifecycle and 40 opcode fragments wired')
    print('PASS all forty-seven i386 COFF source units compile under locked MSVC profile')
    print('PARTIAL source root only; remaining inline cases open, no strict exact-byte credit')


if __name__=='__main__':
    main()
