#!/usr/bin/env python3
"""Fail-closed runtime no-life-decrement patcher for the locked Japanese TH20 Steamless target.

The executable on disk is never modified.  Run through repo-python.cmd with Windows Python; --game-dir selects the
game directory, and --launch starts the verified game before attaching.
"""

from __future__ import annotations

import argparse
import ctypes
import hashlib
import os
import struct
import subprocess
import sys
import time
from ctypes import wintypes
from pathlib import Path


TARGETS = {
    "th20.exe": {
        "sha256": "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897",
        "image_base": 0x00400000,
        "patch_rva": 0x000F849D,
        "old": bytes.fromhex("FF"),
        "new": bytes.fromhex("00"),
        "context_rva": 0x000F849C,
        "context": bytes.fromhex("6A FF 8B 4D D8 E8 AA 8D FE FF"),
        "meaning": "death processing calls add_lives(0) instead of add_lives(-1)",
    },
}

GAME_DIR = Path.cwd()
LOG_PATH = GAME_DIR / "runtime_patch_log.txt"

TH32CS_SNAPPROCESS = 0x00000002
TH32CS_SNAPMODULE = 0x00000008
TH32CS_SNAPMODULE32 = 0x00000010
PROCESS_VM_OPERATION = 0x0008
PROCESS_VM_READ = 0x0010
PROCESS_VM_WRITE = 0x0020
PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000
PAGE_EXECUTE_READWRITE = 0x40
MAX_PATH = 260
INVALID_HANDLE_VALUE = ctypes.c_void_p(-1).value
ERROR_BAD_LENGTH = 24
ERROR_PARTIAL_COPY = 299


def log(message: str) -> None:
    line = f"{time.strftime('%Y-%m-%d %H:%M:%S')} {message}"
    print(line, flush=True)
    with LOG_PATH.open("a", encoding="utf-8", newline="\n") as output:
        output.write(line + "\n")


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def normalized_path(path: Path | str) -> str:
    return os.path.normcase(os.path.abspath(str(path)))


def select_target() -> tuple[str, Path, dict[str, object]]:
    present = []
    for exe_name, spec in TARGETS.items():
        path = GAME_DIR / exe_name
        if path.is_file():
            present.append((exe_name, path, spec))
    if len(present) != 1:
        names = ", ".join(name for name, _path, _spec in present) or "none"
        raise RuntimeError(
            f"expected exactly one supported executable beside this script; found {names}"
        )
    return present[0]


def rva_to_file_offset(data: bytes, rva: int) -> int:
    if data[:2] != b"MZ":
        raise RuntimeError("target is not an MZ executable")
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise RuntimeError("target has no PE signature")
    machine, section_count, _timestamp, _symtab, _symbols, optional_size = (
        struct.unpack_from("<HHIIIH", data, pe_offset + 4)
    )
    if machine != 0x014C:
        raise RuntimeError(f"target is not i386 PE (machine={machine:#x})")
    optional = pe_offset + 24
    if struct.unpack_from("<H", data, optional)[0] != 0x010B:
        raise RuntimeError("target is not PE32")
    section_table = optional + optional_size
    for index in range(section_count):
        entry = section_table + index * 40
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, entry + 8
        )
        mapped_size = max(virtual_size, raw_size)
        if virtual_address <= rva < virtual_address + mapped_size:
            delta = rva - virtual_address
            if delta >= raw_size:
                raise RuntimeError(f"patch RVA {rva:#x} is not file-backed")
            return raw_pointer + delta
    raise RuntimeError(f"patch RVA {rva:#x} is outside PE sections")


def verify_file(path: Path, spec: dict[str, object]) -> None:
    digest = sha256_file(path)
    if digest != spec["sha256"]:
        raise RuntimeError(
            f"target identity mismatch: {path} sha256={digest}; expected={spec['sha256']}"
        )
    data = path.read_bytes()
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    optional = pe_offset + 24
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    if image_base != spec["image_base"]:
        raise RuntimeError(
            f"unexpected preferred image base {image_base:#x}; expected {spec['image_base']:#x}"
        )
    file_offset = rva_to_file_offset(data, int(spec["patch_rva"]))
    old = bytes(spec["old"])
    actual = data[file_offset : file_offset + len(old)]
    if actual != old:
        raise RuntimeError(
            f"unexpected on-disk patch bytes at RVA {spec['patch_rva']:#x}: "
            f"{actual.hex(' ')}; expected {old.hex(' ')}"
        )
    context_offset = rva_to_file_offset(data, int(spec["context_rva"]))
    context = bytes(spec["context"])
    if data[context_offset : context_offset + len(context)] != context:
        raise RuntimeError("unexpected on-disk death call context")
    log(
        f"verified file {path} sha256={digest} "
        f"patch_rva=0x{spec['patch_rva']:08X} bytes={old.hex(' ')}"
    )


class PROCESSENTRY32W(ctypes.Structure):
    _fields_ = [
        ("dwSize", wintypes.DWORD),
        ("cntUsage", wintypes.DWORD),
        ("th32ProcessID", wintypes.DWORD),
        ("th32DefaultHeapID", ctypes.c_size_t),
        ("th32ModuleID", wintypes.DWORD),
        ("cntThreads", wintypes.DWORD),
        ("th32ParentProcessID", wintypes.DWORD),
        ("pcPriClassBase", wintypes.LONG),
        ("dwFlags", wintypes.DWORD),
        ("szExeFile", wintypes.WCHAR * MAX_PATH),
    ]


class MODULEENTRY32W(ctypes.Structure):
    _fields_ = [
        ("dwSize", wintypes.DWORD),
        ("th32ModuleID", wintypes.DWORD),
        ("th32ProcessID", wintypes.DWORD),
        ("GlblcntUsage", wintypes.DWORD),
        ("ProccntUsage", wintypes.DWORD),
        ("modBaseAddr", ctypes.POINTER(wintypes.BYTE)),
        ("modBaseSize", wintypes.DWORD),
        ("hModule", wintypes.HMODULE),
        ("szModule", wintypes.WCHAR * 256),
        ("szExePath", wintypes.WCHAR * MAX_PATH),
    ]


class Win32:
    def __init__(self) -> None:
        if os.name != "nt":
            raise RuntimeError("run this script with Windows Python")
        self.kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
        k32 = self.kernel32
        k32.CreateToolhelp32Snapshot.argtypes = [wintypes.DWORD, wintypes.DWORD]
        k32.CreateToolhelp32Snapshot.restype = wintypes.HANDLE
        k32.Process32FirstW.argtypes = [wintypes.HANDLE, ctypes.POINTER(PROCESSENTRY32W)]
        k32.Process32FirstW.restype = wintypes.BOOL
        k32.Process32NextW.argtypes = [wintypes.HANDLE, ctypes.POINTER(PROCESSENTRY32W)]
        k32.Process32NextW.restype = wintypes.BOOL
        k32.Module32FirstW.argtypes = [wintypes.HANDLE, ctypes.POINTER(MODULEENTRY32W)]
        k32.Module32FirstW.restype = wintypes.BOOL
        k32.Module32NextW.argtypes = [wintypes.HANDLE, ctypes.POINTER(MODULEENTRY32W)]
        k32.Module32NextW.restype = wintypes.BOOL
        k32.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
        k32.OpenProcess.restype = wintypes.HANDLE
        k32.CloseHandle.argtypes = [wintypes.HANDLE]
        k32.CloseHandle.restype = wintypes.BOOL
        k32.QueryFullProcessImageNameW.argtypes = [
            wintypes.HANDLE,
            wintypes.DWORD,
            wintypes.LPWSTR,
            ctypes.POINTER(wintypes.DWORD),
        ]
        k32.QueryFullProcessImageNameW.restype = wintypes.BOOL
        k32.ReadProcessMemory.argtypes = [
            wintypes.HANDLE,
            wintypes.LPCVOID,
            wintypes.LPVOID,
            ctypes.c_size_t,
            ctypes.POINTER(ctypes.c_size_t),
        ]
        k32.ReadProcessMemory.restype = wintypes.BOOL
        k32.WriteProcessMemory.argtypes = [
            wintypes.HANDLE,
            wintypes.LPVOID,
            wintypes.LPCVOID,
            ctypes.c_size_t,
            ctypes.POINTER(ctypes.c_size_t),
        ]
        k32.WriteProcessMemory.restype = wintypes.BOOL
        k32.VirtualProtectEx.argtypes = [
            wintypes.HANDLE,
            wintypes.LPVOID,
            ctypes.c_size_t,
            wintypes.DWORD,
            ctypes.POINTER(wintypes.DWORD),
        ]
        k32.VirtualProtectEx.restype = wintypes.BOOL
        k32.FlushInstructionCache.argtypes = [
            wintypes.HANDLE,
            wintypes.LPCVOID,
            ctypes.c_size_t,
        ]
        k32.FlushInstructionCache.restype = wintypes.BOOL

    def error(self, operation: str) -> OSError:
        code = ctypes.get_last_error()
        return OSError(code, f"{operation}: {ctypes.FormatError(code)}")

    def process_ids(self, exe_name: str) -> tuple[int, ...]:
        snapshot = self.kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
        if snapshot == INVALID_HANDLE_VALUE:
            raise self.error("CreateToolhelp32Snapshot(process)")
        matches = []
        try:
            entry = PROCESSENTRY32W()
            entry.dwSize = ctypes.sizeof(entry)
            ok = self.kernel32.Process32FirstW(snapshot, ctypes.byref(entry))
            while ok:
                if entry.szExeFile.lower() == exe_name.lower():
                    matches.append(int(entry.th32ProcessID))
                ok = self.kernel32.Process32NextW(snapshot, ctypes.byref(entry))
        finally:
            self.kernel32.CloseHandle(snapshot)
        return tuple(matches)

    def image_path(self, pid: int) -> Path:
        handle = self.kernel32.OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, False, pid)
        if not handle:
            raise self.error(f"OpenProcess({pid})")
        try:
            capacity = 32768
            buffer = ctypes.create_unicode_buffer(capacity)
            size = wintypes.DWORD(capacity)
            if not self.kernel32.QueryFullProcessImageNameW(
                handle, 0, buffer, ctypes.byref(size)
            ):
                raise self.error("QueryFullProcessImageNameW")
            return Path(buffer.value)
        finally:
            self.kernel32.CloseHandle(handle)

    def module_base(
        self,
        pid: int,
        exe_name: str,
        expected_path: Path,
        timeout_seconds: float = 10.0,
    ) -> int:
        flags = TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32
        deadline = time.perf_counter() + timeout_seconds
        last_detail = "main module not visible yet"
        while time.perf_counter() < deadline:
            ctypes.set_last_error(0)
            snapshot = self.kernel32.CreateToolhelp32Snapshot(flags, pid)
            if snapshot == INVALID_HANDLE_VALUE:
                code = ctypes.get_last_error()
                last_detail = f"snapshot error {code}: {ctypes.FormatError(code)}"
                # Windows documents ERROR_BAD_LENGTH as a transient module-list
                # race and requires retrying the snapshot.  A newly launched
                # 32-bit process can also briefly report ERROR_PARTIAL_COPY.
                if code not in (ERROR_BAD_LENGTH, ERROR_PARTIAL_COPY):
                    raise self.error("CreateToolhelp32Snapshot(module)")
                time.sleep(0.05)
                continue
            try:
                entry = MODULEENTRY32W()
                entry.dwSize = ctypes.sizeof(entry)
                ok = self.kernel32.Module32FirstW(snapshot, ctypes.byref(entry))
                while ok:
                    if (
                        entry.szModule.lower() == exe_name.lower()
                        and normalized_path(entry.szExePath)
                        == normalized_path(expected_path)
                    ):
                        return int(
                            ctypes.cast(entry.modBaseAddr, ctypes.c_void_p).value
                        )
                    ok = self.kernel32.Module32NextW(snapshot, ctypes.byref(entry))
                code = ctypes.get_last_error()
                last_detail = (
                    f"module enumeration ended with {code}: {ctypes.FormatError(code)}"
                )
            finally:
                self.kernel32.CloseHandle(snapshot)
            time.sleep(0.05)
        raise RuntimeError(
            f"could not find exact main module for pid={pid}: {last_detail}"
        )


def find_exact_process(
    api: Win32,
    exe_name: str,
    expected_path: Path,
    expected_sha256: str,
    timeout_seconds: float,
) -> tuple[int, Path]:
    deadline = time.perf_counter() + timeout_seconds
    last_errors: list[str] = []
    while time.perf_counter() < deadline:
        matches: list[tuple[int, Path]] = []
        last_errors.clear()
        for pid in api.process_ids(exe_name):
            try:
                image_path = api.image_path(pid)
                if normalized_path(image_path) != normalized_path(expected_path):
                    continue
                digest = sha256_file(image_path)
                if digest != expected_sha256:
                    last_errors.append(f"pid={pid}: sha256={digest}")
                    continue
                matches.append((pid, image_path))
            except Exception as exc:
                last_errors.append(f"pid={pid}: {exc}")
        if len(matches) == 1:
            return matches[0]
        if len(matches) > 1:
            raise RuntimeError(
                "refusing ambiguous exact targets: "
                + ", ".join(str(pid) for pid, _path in matches)
            )
        time.sleep(0.25)
    detail = "; ".join(last_errors) if last_errors else f"no {exe_name} process"
    raise RuntimeError(f"exact target process not found: {detail}")


def read_memory(api: Win32, handle: int, address: int, size: int) -> bytes:
    buffer = ctypes.create_string_buffer(size)
    count = ctypes.c_size_t()
    if not api.kernel32.ReadProcessMemory(
        handle, ctypes.c_void_p(address), buffer, size, ctypes.byref(count)
    ) or count.value != size:
        raise api.error(f"ReadProcessMemory({address:#x}, {size})")
    return buffer.raw


def write_memory(api: Win32, handle: int, address: int, data: bytes) -> None:
    old_protection = wintypes.DWORD()
    if not api.kernel32.VirtualProtectEx(
        handle,
        ctypes.c_void_p(address),
        len(data),
        PAGE_EXECUTE_READWRITE,
        ctypes.byref(old_protection),
    ):
        raise api.error("VirtualProtectEx(set)")
    try:
        buffer = ctypes.create_string_buffer(data)
        written = ctypes.c_size_t()
        if not api.kernel32.WriteProcessMemory(
            handle,
            ctypes.c_void_p(address),
            buffer,
            len(data),
            ctypes.byref(written),
        ) or written.value != len(data):
            raise api.error("WriteProcessMemory")
        if not api.kernel32.FlushInstructionCache(
            handle, ctypes.c_void_p(address), len(data)
        ):
            raise api.error("FlushInstructionCache")
    finally:
        restored = wintypes.DWORD()
        if not api.kernel32.VirtualProtectEx(
            handle,
            ctypes.c_void_p(address),
            len(data),
            old_protection.value,
            ctypes.byref(restored),
        ):
            raise api.error("VirtualProtectEx(restore)")


def patch_process(
    exe_name: str, target_path: Path, spec: dict[str, object], timeout: float
) -> None:
    api = Win32()
    pid, image_path = find_exact_process(
        api, exe_name, target_path, str(spec["sha256"]), timeout
    )
    module_base = api.module_base(pid, exe_name, image_path)
    address = module_base + int(spec["patch_rva"])
    access = (
        PROCESS_QUERY_INFORMATION
        | PROCESS_VM_OPERATION
        | PROCESS_VM_READ
        | PROCESS_VM_WRITE
    )
    handle = api.kernel32.OpenProcess(access, False, pid)
    if not handle:
        raise api.error(f"OpenProcess(write, pid={pid})")
    try:
        old = bytes(spec["old"])
        new = bytes(spec["new"])
        actual = read_memory(api, handle, address, len(old))
        log(
            f"verified process path={image_path} pid={pid} "
            f"module_base=0x{module_base:08X} address=0x{address:08X} "
            f"bytes={actual.hex(' ')}"
        )
        context_address = module_base + int(spec["context_rva"])
        context = read_memory(api, handle, context_address, len(bytes(spec["context"])))
        normalized = bytearray(context)
        normalized[int(spec["patch_rva"]) - int(spec["context_rva"])] = old[0]
        if bytes(normalized) != bytes(spec["context"]):
            raise RuntimeError("unexpected live death call context")
        if actual == new:
            log("process is already patched")
            return
        if actual != old:
            raise RuntimeError(
                f"unexpected process bytes at 0x{address:08X}: "
                f"{actual.hex(' ')}; expected {old.hex(' ')}"
            )
        write_memory(api, handle, address, new)
        observed = read_memory(api, handle, address, len(new))
        if observed != new:
            raise RuntimeError(
                f"runtime patch verification failed: read back {observed.hex(' ')}"
            )
        log(
            f"patched memory 0x{address:08X}: {old.hex(' ')} -> {new.hex(' ')}; "
            f"{spec['meaning']}"
        )
    finally:
        api.kernel32.CloseHandle(handle)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--check",
        action="store_true",
        help="verify the adjacent executable and original patch bytes without attaching",
    )
    parser.add_argument(
        "--launch",
        action="store_true",
        help="launch the verified adjacent executable before attaching",
    )
    parser.add_argument("--game-dir", type=Path, default=Path.cwd())
    parser.add_argument("--timeout", type=float, default=15.0)
    return parser.parse_args()


def main() -> int:
    global GAME_DIR, LOG_PATH
    args = parse_args()
    GAME_DIR = args.game_dir.resolve()
    LOG_PATH = GAME_DIR / "runtime_patch_log.txt"
    exe_name, target_path, spec = select_target()
    log(f"runtime patcher started for {exe_name}")
    verify_file(target_path, spec)
    if args.check:
        log("offline check passed; executable was not modified")
        return 0
    launched = None
    if args.launch:
        launched = subprocess.Popen([str(target_path)], cwd=str(GAME_DIR))
        log(f"launched {exe_name} pid={launched.pid}")
    try:
        patch_process(exe_name, target_path, spec, args.timeout)
    except Exception:
        if launched is not None and launched.poll() is None:
            launched.terminate()
            log(f"terminated unpatched launch pid={launched.pid}")
        raise
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as exc:
        log(f"error: {exc}")
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
