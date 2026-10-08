#include "PbgFile.hpp"
#include "WideSecureCrt.hpp"
// Execute actual production bodies; fixtures only cover Win32 calls and the
// valid-input secure wchar CRT. ASCII names, host wchar4/native wchar2.
#include <algorithm>
#include <cstring>
#include <cassert>
#include <memory>
#include <string>
#include <vector>

namespace {
struct Handle {
    unsigned closes=0,reads=0,writes=0,seeks=0;
    DWORD access=0,position=0;
    std::string bytes="ABCDE";
};
std::vector<std::unique_ptr<Handle>> handles;
std::wstring module=L"Z:\\games\\th20.exe",last_path;
DWORD last_access=0,last_creation=0;
unsigned module_calls=0,conversions=0,open_calls=0,invalid_reads=0;
bool fail_open=false,fail_conversion=false,read_boolean=true,write_boolean=true,fail_seek=false;
DWORD read_limit=~DWORD{0},write_limit=~DWORD{0},forced_size=0;
Handle* current(HANDLE handle) {
    if (handle==INVALID_HANDLE_VALUE) return nullptr;
    auto* result=static_cast<Handle*>(handle);
    assert(result && result->closes==0);
    return result;
}
void reset_io() {
    read_limit=write_limit=~DWORD{0};
    read_boolean=write_boolean=true;
    fail_open=fail_conversion=fail_seek=false;
    forced_size=0;
}
}
extern "C" HANDLE CreateFileW(const wchar_t* path,DWORD access,DWORD share,void* security,DWORD creation,DWORD flags,HANDLE owner) {
    assert(share==FILE_SHARE_READ && !security && !owner);
    assert(flags==(FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN));
    last_path=path;last_access=access;last_creation=creation;++open_calls;
    if (fail_open) return INVALID_HANDLE_VALUE;
    auto value=std::make_unique<Handle>();value->access=access;
    auto* result=value.get();handles.push_back(std::move(value));return result;
}
extern "C" int CloseHandle(HANDLE handle) { auto* h=current(handle);assert(h);++h->closes;return 0; }
extern "C" DWORD GetFileSize(HANDLE handle,DWORD* high) {
    assert(!high);auto* h=current(handle);assert(h);
    return forced_size ? forced_size : static_cast<DWORD>(h->bytes.size());
}
extern "C" DWORD SetFilePointer(HANDLE handle,std::int32_t offset,std::int32_t* high,DWORD origin) {
    assert(!high);auto* h=current(handle);assert(h);++h->seeks;
    if (fail_seek) return ~DWORD{0};
    if (origin==0) h->position=offset;
    else if (origin==FILE_CURRENT) h->position+=offset;
    else { assert(origin==FILE_END);h->position=h->bytes.size()+offset; }
    return h->position;
}
extern "C" int ReadFile(HANDLE handle,void* destination,DWORD extent,DWORD* count,void* overlapped) {
    assert(!overlapped && count);auto* h=current(handle);
    if (!h) { ++invalid_reads;*count=0;return 0; }
    assert(h->access==GENERIC_READ);++h->reads;
    *count=std::min({extent,read_limit,static_cast<DWORD>(h->bytes.size()-h->position)});
    std::memcpy(destination,h->bytes.data()+h->position,*count);h->position+=*count;
    return read_boolean;
}
extern "C" int WriteFile(HANDLE handle,const void* input,DWORD extent,DWORD* count,void* overlapped) {
    assert(!overlapped && count);auto* h=current(handle);assert(h && h->access==GENERIC_WRITE);++h->writes;
    *count=std::min(extent,write_limit);
    h->bytes.resize(std::max<std::size_t>(h->bytes.size(),h->position+*count));
    std::memcpy(h->bytes.data()+h->position,input,*count);h->position+=*count;
    return write_boolean;
}
extern "C" int MultiByteToWideChar(unsigned page,DWORD flags,const char* source,int size,wchar_t* destination,int capacity) {
    assert(page==932 && flags==0 && size==-1 && capacity==260);++conversions;
    if (fail_conversion) return 0;
    const auto extent=std::strlen(source);assert(extent+1<=static_cast<unsigned>(capacity));
    for (unsigned i=0;i<=extent;++i) { assert(static_cast<unsigned char>(source[i])<128);destination[i]=source[i]; }
    return extent+1;
}
extern "C" DWORD GetModuleFileNameW(HANDLE handle,wchar_t* destination,DWORD capacity) {
    assert(!handle && capacity==260 && module.size()+1<=capacity);++module_calls;
    std::wcscpy(destination,module.c_str());return module.size();
}
extern "C" int wcscpy_s(wchar_t* destination,std::size_t capacity,const wchar_t* source) {
    assert(destination && source && std::wcslen(source)<capacity);std::wcscpy(destination,source);return 0;
}
extern "C" int wcscat_s(wchar_t* destination,std::size_t capacity,const wchar_t* source) {
    assert(destination && source && std::wcslen(destination)+std::wcslen(source)<capacity);std::wcscat(destination,source);return 0;
}

int main() {
    using Pbg::File;
    reset_io();
    {
        File file;
        assert(file.handle==INVALID_HANDLE_VALUE && file.access==0);
        assert(file.position()==0 && file.size()==0 && !file.seek(0,0));
        char output[8]={};assert(file.read(output,1)==0 && !file.write("x",1));
        assert(!file.open("x","w") && !file.open("x",""));
        assert(open_calls==0 && conversions==0);
        assert(file.open("member.bin","xxrb"));
        auto* handle=current(file.handle);
        assert(last_path==L"Z:\\games\\member.bin" && last_access==GENERIC_READ && last_creation==OPEN_EXISTING);
        assert(file.size()==5 && file.position()==0 && !file.write("x",1));
        assert(handle->writes==0);
        read_limit=3;read_boolean=false;
        assert(file.read(output,5)==3 && std::string(output,3)=="ABC");
        assert(file.position()==3 && handle->reads==1);
        read_limit=~DWORD{0};read_boolean=true;
        assert(file.read(output,5)==2 && std::string(output,2)=="DE");
        assert(file.seek(-2,FILE_CURRENT) && file.position()==3);
        fail_seek=true;
        assert(file.seek(1,0) && file.position()==~DWORD{0});
        fail_seek=false;
        forced_size=~DWORD{0};assert(file.size()==~DWORD{0});forced_size=0;
        file.close();assert(handle->closes==1 && file.handle==INVALID_HANDLE_VALUE && file.access==0);
        file.close();assert(handle->closes==1);
    }
    reset_io();
    {
        File file;
        assert(file.open("C:relative.bin","abr"));
        auto* handle=current(file.handle);
        assert(last_path==L"C:relative.bin" && last_access==GENERIC_WRITE && last_creation==OPEN_ALWAYS);
        assert(handle->position==5 && handle->seeks==1);
        char output[3]={};assert(file.read(output,3)==0 && handle->reads==0);
        write_boolean=false;
        assert(file.write("FG",2) && handle->bytes=="ABCDEFG");
        write_limit=1;
        assert(!file.write("HI",2) && handle->bytes=="ABCDEFGH");
        assert(file.open("other.bin","r") && handle->closes==1);
    }
    reset_io();
    {
        File file;
        fail_open=true;
        assert(!file.open("missing.bin","r"));
        assert(file.handle==INVALID_HANDLE_VALUE && file.access==GENERIC_READ);
        file.close();assert(file.access==GENERIC_READ);
        char output[1]={};auto old=invalid_reads;assert(file.read(output,1)==0 && invalid_reads==old+1);
        assert(!file.open("missing.bin","w") && file.access==GENERIC_READ);
        fail_open=false;
        assert(file.open("member.bin","r"));
    }
    reset_io();
    {
        File file;
        module=L"th20.exe";
        assert(file.open("relative.bin","r") && last_path==L"relative.bin");
        module=L"Z:\\games\\th20.exe";
        assert(file.open("\\\\server\\asset","r") && last_path==L"Z:\\games\\\\\\server\\asset");
        fail_conversion=true;
        assert(file.open("ignored.bin","r") && last_path==L"Z:\\games\\");
    }
    reset_io();
    {
        struct CountClose : File {
            unsigned calls=0;
            void close() override { ++calls;File::close(); }
        } file;
        assert(file.open("member.bin","r") && file.calls==1);
        assert(file.open("member.bin","a") && file.calls==2);
    }
    for (const auto& handle:handles) assert(handle->closes==1);
    assert(module_calls>0);
}
