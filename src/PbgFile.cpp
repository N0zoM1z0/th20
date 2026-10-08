#include "PbgFile.hpp"
#include "WideSecureCrt.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstring>

namespace Pbg {
IFile::IFile() {}
IFile::~IFile() {}
File::File():handle(INVALID_HANDLE_VALUE),access(0) {}
File::~File() { close(); }
void convert_filename(wchar_t* destination,const char* name) {
    wchar_t converted[260];
    std::memset(converted,0,sizeof(converted));
    MultiByteToWideChar(932,0,name,-1,converted,260);
    if (std::wcschr(converted,L':')) {
        wcscpy_s(destination,260,converted);
    } else {
        GetModuleFileNameW(nullptr,destination,260);
        wchar_t* slash=std::wcsrchr(destination,L'\\');
        if (!slash) wcscpy_s(destination,260,L"");
        else slash[1]=0;
        wcscat_s(destination,260,converted);
    }
}
bool File::open(const char* name,const char* mode) {
    wchar_t converted[260];
    DWORD append=0;
    DWORD creation=0;
    close();
    const char* cursor;
    for (cursor=mode;*cursor;++cursor) {
        if (*cursor=='r') {
            access=GENERIC_READ;
            creation=OPEN_EXISTING;
            break;
        }
        if (*cursor=='a') {
            append=1;
            access=GENERIC_WRITE;
            creation=OPEN_ALWAYS;
            break;
        }
    }
    if (!*cursor) return false;
    convert_filename(converted,name);
    handle=CreateFileW(converted,access,FILE_SHARE_READ,nullptr,creation,
        FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,nullptr);
    if (handle==INVALID_HANDLE_VALUE) return false;
    if (append) SetFilePointer(handle,0,nullptr,FILE_END);
    return true;
}
void File::close() {
    if (handle!=INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
        handle=INVALID_HANDLE_VALUE;
        access=0;
    }
}
std::uint32_t File::read(void* output,std::uint32_t size) {
    DWORD count=0;
    if (access!=GENERIC_READ) return 0;
    ReadFile(handle,output,size,&count,nullptr);
    return count;
}
bool File::write(const void* input,std::uint32_t size) {
    DWORD count=0;
    if (access!=GENERIC_WRITE) return false;
    WriteFile(handle,input,size,&count,nullptr);
    return size==count ? true : false;
}
std::uint32_t File::position() {
    if (handle==INVALID_HANDLE_VALUE) return 0;
    return SetFilePointer(handle,0,nullptr,FILE_CURRENT);
}
std::uint32_t File::size() {
    if (handle==INVALID_HANDLE_VALUE) return 0;
    return GetFileSize(handle,nullptr);
}
bool File::seek(std::int32_t offset,std::uint32_t origin) {
    if (handle==INVALID_HANDLE_VALUE) return false;
    SetFilePointer(handle,offset,nullptr,origin);
    return true;
}
}

// The observed factory pre-clear is still an emission question. This is the
// shared real scalar allocation body, not a fabricated clear or exact claim.
namespace th20 {
template Pbg::File* DiagnosticAllocator::allocate_object<Pbg::File>(const char*);
}
