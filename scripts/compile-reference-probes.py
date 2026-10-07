#!/usr/bin/env python3
"""Serial unmodified reference TU diagnostics; compilation confers no credit."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import subprocess
import sys

from project import ROOT, attest_compiler, digest, load_manifest, verified_target, verify_build_receipt

PROFILE = ["/nologo", "/c", "/std:c++20", "/Od", "/Ob0", "/GS-", "/Gy",
           "/Zl", "/arch:SSE2", "/fp:precise", "/EHsc", "/utf-8", "/MT"]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--module", action="append", default=[])
    parser.add_argument("--source", action="append", default=[],
                        help="Limit compilation to exact reference-relative TU paths")
    parser.add_argument("--resume", action="store_true")
    args = parser.parse_args()
    pin = load_manifest("reference.toml")
    reference = ROOT / pin["local_path"]
    # runtime_core exports the scheduler include directory through its CMake
    # dependency. Record the corresponding include in this diagnostic recipe.
    scheduler_include = reference / "source_reconstruction/core_scheduler"
    include_profile = PROFILE + ["/IZ:" + str(scheduler_include.resolve()).replace("/", "\\")]
    if subprocess.check_output(["git", "-C", str(reference), "rev-parse", "HEAD"], text=True).strip() != pin["commit"]:
        raise ValueError("reference commit differs")
    if subprocess.check_output(["git", "-C", str(reference), "status", "--porcelain"], text=True):
        raise ValueError("reference checkout is dirty")
    verified_target()
    compiler, _ = attest_compiler()
    with (ROOT / "config/reference-source-files.csv").open(newline="") as stream:
        files = [row for row in csv.DictReader(stream)
                 if row["role_hint"] == "reconstruction-candidate"
                 and Path(row["reference_path"]).suffix == ".cpp"]
    if args.module:
        files = [row for row in files if (row["reference_path"].split("/")[1]
                 if row["reference_path"].startswith("source_reconstruction/")
                 else row["reference_path"].split("/")[0]) in args.module]
    if args.source:
        unknown = set(args.source) - {row["reference_path"] for row in files}
        if unknown:
            raise ValueError(f"unconfigured reference sources: {sorted(unknown)}")
        files = [row for row in files if row["reference_path"] in args.source]
    output = ROOT / ".analysis/reference-functions/compilations"
    output.mkdir(parents=True, exist_ok=True)
    for index, row in enumerate(files, 1):
        relative = row["reference_path"]
        source = reference / relative
        if digest(source) != row["file_sha256"]:
            raise ValueError(f"reference source inventory is stale: {relative}")
        profile = list(include_profile)
        if relative.startswith("source_reconstruction/ecl_vm/"):
            # ECL declares native headers and inherits binary headers. Preserve
            # its strict FP and conforming-language options in the diagnostic.
            for directory in ("native_recovered", "include"):
                profile.append("/IZ:" + str((reference / directory).resolve()).replace("/", "\\"))
            profile[profile.index("/fp:precise")] = "/fp:strict"
            profile.append("/permissive-")
        if relative.startswith(("source_reconstruction/runtime_state/",
                                "source_reconstruction/platform_window/",
                                "source_reconstruction/startup_scene/",
                                "source_reconstruction/stage_clear/",
                                "source_reconstruction/help_system/",
                                "source_reconstruction/notice_system/",
                                "source_reconstruction/card_system/",
                                "source_reconstruction/ending_scene/",
                                "source_reconstruction/trophy_system/",
                                "source_reconstruction/screen_effect/",
                                "source_reconstruction/text_renderer/",
                                "source_reconstruction/options_system/",
                                "source_reconstruction/key_config/",
                                "source_reconstruction/pause_system/",
                                "source_reconstruction/stone_menu/",
                                "source_reconstruction/progress_state/",
                                "source_reconstruction/replay_system/",
                                "source_reconstruction/title_system/",
                                "source_reconstruction/effect_system/",
                                "source_reconstruction/special_state/",
                                "source_reconstruction/bullet_system/",
                                "source_reconstruction/laser_system/",
                                "source_reconstruction/damage_regions/",
                                "source_reconstruction/player_entity/",
                                "source_reconstruction/bomb_system/",
                                "source_reconstruction/item_system/",
                                "source_reconstruction/overlay_system/",
                                "source_reconstruction/hud_system/",
                                "source_reconstruction/small_score/",
                                "source_reconstruction/stage_completion/",
                                "source_reconstruction/gameplay/",
                                "source_reconstruction/sprite_renderer/",
                                "source_reconstruction/stage_background/")):
            # runtime_state exports ecl_vm's includes. platform_window links
            # runtime_state and also declares native/binary includes itself;
            # startup_scene inherits platform_window and declares those paths;
            # stage_clear links runtime_state's public ecl/binary include paths.
            # help_system also declares binary includes and inherits ECL/runtime
            # paths through sprite_renderer and stone_menu.
            # notice_system has the same declared binary paths and links help
            # and stone_menu, including their transitive ECL/runtime paths.
            # card_system links runtime_state's public ECL/binary dependencies.
            # ending_scene inherits these paths through sprite_renderer's ECL.
            # trophy_system links the same public sprite/ECL dependencies.
            # screen_effect inherits these paths through sprite/runtime/gameplay.
            # text_renderer declares binary paths and links sprite/runtime.
            # options/key menus declare these paths and inherit sprite/ECL.
            # pause/stone menus declare these paths and inherit game/sprite/ECL.
            # Progress declares native/binary paths; Replay inherits them from
            # Progress, gameplay, overlay and platform-window dependencies.
            # Title declares native/binary/scheduler paths and inherits ECL
            # through its public stone-menu and runtime dependencies.
            # Effect and Special State declare native/binary/scheduler paths;
            # their public runtime/VM dependencies propagate ECL headers.
            # Bullet, Laser and Damage Regions inherit the same runtime/VM
            # headers; Damage also explicitly declares native/binary/scheduler.
            # Player inherits ECL/session/runtime headers and declares native/
            # scheduler; Bomb inherits gameplay/sprite/runtime/Damage; Item
            # declares native/binary/scheduler and inherits runtime/sprite.
            # Overlay, HUD, Small Score and Stage Completion declare these
            # paths and inherit runtime/VM headers through their public links.
            # Preserve the paths propagated by the reviewed CMake recipes.
            for directory in ("source_reconstruction/ecl_vm", "native_recovered", "include"):
                profile.append("/IZ:" + str((reference / directory).resolve()).replace("/", "\\"))
        if relative.startswith("source_reconstruction/sprite_renderer/"):
            # The renderer and platform adapter request strict FP; its entry
            # adapter is a separate target without that CMake option.
            if Path(relative).name not in {
                    "entry_adapter.cpp", "anm_adapter.cpp", "controller_adapter.cpp"}:
                profile[profile.index("/fp:precise")] = "/fp:strict"
        if relative.startswith(("source_reconstruction/text_renderer/",
                                "source_reconstruction/options_system/",
                                "source_reconstruction/key_config/",
                                "source_reconstruction/pause_system/",
                                "source_reconstruction/stone_menu/",
                                "source_reconstruction/progress_state/",
                                "source_reconstruction/replay_system/",
                                "source_reconstruction/title_system/",
                                "source_reconstruction/effect_system/",
                                "source_reconstruction/special_state/",
                                "source_reconstruction/bullet_system/",
                                "source_reconstruction/laser_system/",
                                "source_reconstruction/damage_regions/",
                                "source_reconstruction/player_entity/",
                                "source_reconstruction/bomb_system/",
                                "source_reconstruction/item_system/",
                                "source_reconstruction/overlay_system/",
                                "source_reconstruction/hud_system/",
                                "source_reconstruction/small_score/",
                                "source_reconstruction/stage_completion/",
                                "source_reconstruction/stage_background/")):
            # Preserve these modules' explicit CMake floating-point option.
            profile[profile.index("/fp:precise")] = "/fp:strict"
        if relative == "source_reconstruction/archive/verify.cpp":
            # These string macros are declared by archive/CMakeLists.txt;
            # preserve the recipe instead of editing unmodified reference code.
            for extension in ("cpp", "hpp"):
                fingerprint = digest(source.parent / f"archive.{extension}")
                profile.append(f'/DTH20_ARCHIVE_{extension.upper()}_SHA256="{fingerprint}"')
        if relative.startswith("source_reconstruction/gameplay/"):
            # The gameplay/Enemy libraries request strict FP; the entry adapter
            # is a distinct target whose reviewed CMake recipe does not.
            strict_sources = {
                "gameplay.cpp", "player_state.cpp", "stage_data.cpp", "loading.cpp",
                "enemy.cpp", "enemy_data.cpp", "enemy_frame.cpp", "enemy_state.cpp",
                "enemy_variables.cpp", "enemy_update.cpp", "enemy_interpolation.cpp",
                "enemy_movement.cpp", "enemy_damage_helpers.cpp", "enemy_damage.cpp",
                "enemy_spawn.cpp", "enemy_entity.cpp", "enemy_vm.cpp", "enemy_reads.cpp",
                "script_loader.cpp", "script_program.cpp", "enemy_opcode_animation.cpp",
                "enemy_opcode_movement.cpp", "enemy_shot.cpp", "enemy_opcode_laser.cpp",
                "enemy_opcode_misc.cpp", "enemy_mesh.cpp", "enemy_defeat.cpp",
                "enemy_opcode_state.cpp", "enemy_drop.cpp", "enemy_cleanup.cpp",
            }
            if Path(relative).name in strict_sources:
                profile[profile.index("/fp:precise")] = "/fp:strict"
        if relative == "source_reconstruction/title_system/replay_format_probe.cpp":
            # This standalone diagnostic is owned by sprite_renderer/pool_test,
            # whose CMake target declares the native fixture's required macro.
            profile.append('/DTH20_NATIVE_CORE_SHA256="unused"')
        key = hashlib.sha256(relative.encode()).hexdigest()[:20]
        report = output / f"{key}.json"
        identity = dict(reference_commit=pin["commit"], reference_path=relative,
                        file_sha256=row["file_sha256"], profile=profile,
                        compiler_sha256=compiler["files"]["bin/HostX64/x86/cl.exe"],
                        target_sha256=pin["target_sha256"])
        object_path = ROOT / "build/reference-probes" / f"{key}.obj"
        if args.resume and report.exists():
            old = json.loads(report.read_text())
            if old.get("result") == "compiled" and all(old.get(field) == value for field, value in identity.items()):
                try:
                    if digest(object_path) != old.get("object_sha256") or digest(object_path.with_suffix(".receipt.json")) != old.get("receipt_sha256"):
                        raise ValueError("cached object/receipt digest differs")
                    verify_build_receipt(dict(object=str(object_path.relative_to(ROOT)),
                                              source=str(source.relative_to(ROOT)), profile=profile))
                except (OSError, ValueError, KeyError):
                    pass  # Retry missing/stale objects, headers and receipts.
                else:
                    print(f"[{index}/{len(files)}] cached compiled: {relative}", flush=True)
                    continue
        command = [str(ROOT / "scripts/compile-probe.sh"), str(source), str(object_path), *profile]
        with (output / f"{key}.log").open("w") as log:
            process = subprocess.run(command, cwd=ROOT, stdout=log, stderr=subprocess.STDOUT)
        result = dict(identity, result="compiled" if process.returncode == 0 else "compile-error",
                      exit_code=process.returncode, object=str(object_path.relative_to(ROOT)),
                      log=f".analysis/reference-functions/compilations/{key}.log")
        if process.returncode == 0:
            result["object_sha256"] = digest(object_path)
            result["receipt_sha256"] = digest(object_path.with_suffix(".receipt.json"))
        report.write_text(json.dumps(result, indent=2) + "\n")
        print(f"[{index}/{len(files)}] {result['result']}: {relative}", flush=True)
    print("Reference compiler diagnostics complete for selected TUs; no semantic review or exact credit inferred.")


if __name__ == "__main__":
    main()
