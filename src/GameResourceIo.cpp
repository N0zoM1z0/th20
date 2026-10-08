#include "GameResourceIo.hpp"
#include "ArchiveOwner.hpp"
#include "EclDiagnostic.hpp"
#include <filesystem>

namespace th20 {
std::uint8_t* read_game_resource(const char* filename,std::int32_t* size,std::int32_t mode) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    const char* member;
    std::int32_t extent;
    std::uint8_t* bytes;
    HANDLE file;
    if (!mode) {
        member=std::strrchr(filename,'\\');
        if (!member) member=filename;else ++member;
        member=std::strrchr(member,'/');
        if (!member) member=filename;else ++member;
        extent=archive_owner.size(member);
        if (size) *size=extent;
        if (!extent) goto fail;
        if (extent) {
            ecl_diagnostic_hint("%s Decode ... \r\n",member);
            bytes=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(extent,filename));
            if (!bytes) goto fail;
            archive_owner.read(member,bytes);
            goto success;
        }
    }
    ecl_diagnostic_hint("%s Load ... \r\n",filename);
    {
        std::filesystem::path path(filename);
        file=CreateFileW(TH20_FILE_NATIVE_NAME(path),GENERIC_READ,FILE_SHARE_READ,
            nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,nullptr);
    }
    if (file==INVALID_HANDLE_VALUE) {
        ecl_diagnostic_hint("error : %s is not found.\r\n",filename);
        goto fail;
    }
    extent=GetFileSize(file,nullptr);
    bytes=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(extent,filename));
    if (!bytes) {
        ecl_diagnostic_hint("error : %s allocation error.\r\n",filename);
        CloseHandle(file);
        goto fail;
    }
    ReadFile(file,bytes,extent,reinterpret_cast<DWORD*>(&extent),nullptr);
    if (size) *size=extent;
    CloseHandle(file);
success:
    return bytes;
fail:
    return nullptr;
}
}
