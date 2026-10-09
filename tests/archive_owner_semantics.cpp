#include "ArchiveOwner.hpp"
#include "ArchiveCrypt.hpp"
#include "ArchiveLzss.hpp"
#include "GameResourceIo.hpp"
#include "SecureCrt.hpp"
#include "WideSecureCrt.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace th20 {
// Explicit process-startup/data fixtures. These define only consumed parameter
// fields; they do not claim the unused native bytes or full table initialization.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
ArchiveOwner archive_owner;
const char* archive_read_mode="r";
std::uint32_t archive_seek_start=0;
ArchiveCipherParameters archive_member_parameters[8]={
    {0x1b,0x73,0x100,0x3800},{0x12,0x43,0x200,0x3e00},
    {0x35,0x79,0x400,0x3c00},{0x03,0x91,0x80,0x6400},
    {0xab,0xdc,0x80,0x7000},{0x51,0x9e,0x100,0x4000},
    {0xc1,0x15,0x400,0x2c00},{0x99,0x7d,0x80,0x4400}
};
}
namespace {
using namespace th20;
using Bytes=std::vector<std::uint8_t>;
struct Allocation { void* pointer;std::size_t size;bool live; };
std::vector<Allocation> allocations;
bool track_malloc=false;
unsigned malloc_calls=0,fail_malloc_call=0;
struct Handle { Bytes bytes;std::size_t position=0;unsigned closes=0,reads=0; };
std::vector<std::unique_ptr<Handle>> handles;
std::map<std::wstring,Bytes> disk;
std::vector<std::wstring> opened;
bool zero_read=false,false_read=false;
unsigned fail_open_call=0;
DWORD read_limit=~DWORD{0};
Handle& handle(HANDLE p) {
    assert(p!=INVALID_HANDLE_VALUE && p);
    auto& result=*static_cast<Handle*>(p);assert(result.closes==0);return result;
}
void reset_failures() { zero_read=false_read=false;fail_open_call=0;read_limit=~DWORD{0};fail_malloc_call=0;malloc_calls=0; }
std::size_t live_allocations() { return std::count_if(allocations.begin(),allocations.end(),[](const auto& r){return r.live;}); }
bool live(void* p) { for (auto r=allocations.rbegin();r!=allocations.rend();++r) if(r->pointer==p)return r->live;return false; }
struct Tokens {
    Bytes bytes;unsigned used=0;
    void bits(unsigned value,unsigned count) {
        for(unsigned bit=count;bit;--bit) {
            if(used%8==0)bytes.push_back(0);
            bytes.back()|=((value>>(bit-1))&1)<<(7-used%8);++used;
        }
    }
    Bytes literals(const Bytes& plain) {
        for(auto b:plain) { bits(1,1);bits(b,8); }
        bits(0,1);bits(0,13);bytes.push_back(0); // Readable decoder guard.
        return bytes;
    }
};
struct Member { std::string name;Bytes decoded;bool compressed=false;std::int32_t offset=0; };
void word(Bytes& bytes,std::uint32_t value) { for(unsigned i=0;i<4;++i)bytes.push_back(value>>(8*i)); }
Bytes pattern(unsigned n,unsigned seed) { Bytes result(n);for(unsigned i=0;i<n;++i)result[i]=(i*37+seed)&255;return result; }
Bytes archive(std::vector<Member>& members) {
    Bytes output(16);
    for(auto& member:members) {
        member.offset=output.size();
        auto stored=member.compressed ? Tokens{}.literals(member.decoded) : member.decoded;
        auto parameter=archive_name_sum(member.name.c_str(),member.name.size())%8;
        const auto& cipher=archive_member_parameters[parameter];
        if(!stored.empty())archive_encrypt(stored.data(),stored.size(),cipher.key,cipher.step,cipher.block,cipher.limit);
        output.insert(output.end(),stored.begin(),stored.end());
    }
    Bytes catalog;
    for(const auto& member:members) {
        catalog.insert(catalog.end(),member.name.begin(),member.name.end());catalog.push_back(0);
        while(catalog.size()%4)catalog.push_back(0);
        word(catalog,member.offset);word(catalog,member.decoded.size());word(catalog,0x12345678);
    }
    word(catalog,0); // Final advance_word still dereferences this readable word.
    auto stored=Tokens{}.literals(catalog);
    archive_encrypt(stored.data(),stored.size(),0x3e,0x9b,128,stored.size());
    output.insert(output.end(),stored.begin(),stored.end());
    ArchiveHeader header{0x31414854,static_cast<std::int32_t>(catalog.size()+123456789),
        static_cast<std::int32_t>(stored.size()+987654321),static_cast<std::int32_t>(members.size()+135792468)};
    archive_encrypt(reinterpret_cast<std::uint8_t*>(&header),sizeof(header),0x1b,0x37,16,16);
    std::memcpy(output.data(),&header,sizeof(header));return output;
}
void exercise_archive(std::vector<Member>& members) {
    auto& owner=archive_owner;
    assert(owner.open("fixture.dat") && owner.count==static_cast<std::int32_t>(members.size()));
    assert(owner.entries && owner.stream && owner.filename && std::string(owner.filename)=="fixture.dat");
    auto* first=owner.find("ENTRY0.DAT");assert(first==owner.entries);
    assert(owner.find("missing")==nullptr && owner.size("missing")==0);
    assert(owner.size("ENTRY0.DAT")==512);
    assert(owner.entries[owner.count].name==nullptr && owner.entries[owner.count].decoded_size==0);
    assert(owner.entries[owner.count].offset==members.back().offset);
    for(unsigned i=0;i<8;++i) {
        assert(owner.entries[i].offset==members[i].offset && owner.entries[i].field_0c==0x12345678);
        Bytes output(members[i].decoded.size(),0);
        std::string upper=members[i].name;for(auto& b:upper)b=std::toupper(static_cast<unsigned char>(b));
        assert(owner.read(upper.c_str(),output.data())==output.data() && output==members[i].decoded);
    }
    // Compressed null destination returns live C-heap decoder storage.
    auto* decoded=owner.read("entry1.dat",nullptr);assert(decoded && live(decoded));
    assert(std::equal(members[1].decoded.begin(),members[1].decoded.end(),decoded));
    process_allocator->release_bytes(decoded);
    // Native uncompressed null destination returns its already released temp.
    const auto before=allocations.size();
    auto* dangling=owner.read("entry2.dat",nullptr);
    assert(dangling && allocations.size()==before+1 && allocations.back().pointer==dangling && !allocations.back().live);
    assert(owner.read("missing",nullptr)==nullptr);
    std::int32_t size=-1;
    auto* resource=read_game_resource("folder/ENTRY0.DAT",&size,0);
    assert(resource && size==512 && std::equal(members[0].decoded.begin(),members[0].decoded.end(),resource));
    process_allocator->release_bytes(resource);
    resource=read_game_resource("folder\\sub/entry1.dat",nullptr,0);
    assert(resource && std::equal(members[1].decoded.begin(),members[1].decoded.end(),resource));
    process_allocator->release_bytes(resource);
    // Missing slash restores the original name after a successful backslash trim.
    const auto opens=opened.size();
    assert(read_game_resource("folder\\entry0.dat",&size,0)==nullptr && size==0 && opened.size()==opens);
    size=-1;assert(read_game_resource("zero.dat",&size,0)==nullptr && size==0 && opened.size()==opens);
    size=-1;assert(read_game_resource("missing",&size,0)==nullptr && size==0 && opened.size()==opens);
    // A failed member read frees caller storage, and resource ignores that result.
    zero_read=true;
    auto* destination=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(512,"caller"));
    assert(owner.read("entry0.dat",destination)==nullptr && !live(destination));
    const auto count=allocations.size();
    auto* ignored=read_game_resource("entry0.dat",&size,0);
    assert(ignored && size==512 && allocations.size()==count+1 && !allocations.back().live);
    zero_read=false;
    // Real File seek rejects its closed handle; owner retains native cleanup.
    owner.stream->close();
    destination=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(512,"caller"));
    assert(owner.read("entry0.dat",destination)==nullptr && !live(destination));
    assert(owner.stream->open(owner.filename,archive_read_mode));
    Bytes saved_dictionary(archive_dictionary,archive_dictionary+8192);
    owner.close();assert(!owner.entries && !owner.stream && !owner.filename && owner.count==0);
    assert(std::equal(saved_dictionary.begin(),saved_dictionary.end(),archive_dictionary));
    assert(live_allocations()==0);owner.close();assert(live_allocations()==0);
}
void exercise_failures() {
    auto& owner=archive_owner;
    fail_open_call=opened.size()+1;
    assert(!owner.open("fixture.dat") && !owner.stream && !owner.entries && owner.count==0 && live_allocations()==0);
    reset_failures();
    // Reopening after a successful catalog load ignores the boolean failure.
    fail_open_call=opened.size()+2;
    assert(owner.open("fixture.dat") && owner.stream->handle==INVALID_HANDLE_VALUE);
    owner.close();assert(live_allocations()==0);reset_failures();
    for(unsigned failure : {1u,2u,13u}) {
        fail_malloc_call=failure;malloc_calls=0;
        // Ten member names plus stored/decoded catalog allocations precede the
        // owner's filename copy, so its failure occurs at call thirteen.
        assert(!owner.open("fixture.dat"));owner.close();assert(live_allocations()==0);reset_failures();
    }
    fail_malloc_call=3;malloc_calls=0;
    assert(owner.open("fixture.dat") && owner.entries[0].name==nullptr);
    owner.close();assert(live_allocations()==0);reset_failures();
    zero_read=true;
    assert(!owner.open("fixture.dat") && live_allocations()==0);reset_failures();
    disk[L"Z:\\game\\bad.dat"]=Bytes(16,0);
    assert(!owner.open("bad.dat") && live_allocations()==0);
}
void exercise_loose() {
    disk[L"loose.bin"]=pattern(31,11);
    std::int32_t size=-1;
    false_read=true;read_limit=7;
    auto* result=read_game_resource("loose.bin",&size,2);
    assert(result && size==7 && std::equal(disk[L"loose.bin"].begin(),disk[L"loose.bin"].begin()+7,result));
    process_allocator->release_bytes(result);reset_failures();
    size=-1;assert(read_game_resource("not-present",&size,1)==nullptr && size==-1);
    fail_malloc_call=1;malloc_calls=0;
    assert(read_game_resource("loose.bin",&size,1)==nullptr && handles.back()->closes==1);
    reset_failures();assert(live_allocations()==0);
}
}
extern "C" void* __real_malloc(std::size_t);
extern "C" void __real_free(void*);
extern "C" void* __wrap_malloc(std::size_t size) {
    if(track_malloc && ++malloc_calls==fail_malloc_call)return nullptr;
    auto* p=__real_malloc(size);
    if(track_malloc && p) allocations.push_back({p,size,true});
    return p;
}
extern "C" void __wrap_free(void* p) {
    if(track_malloc && p) {
        auto row=std::find_if(allocations.rbegin(),allocations.rend(),[&](const auto& r){return r.pointer==p && r.live;});
        assert(row!=allocations.rend());row->live=false;
    }
    __real_free(p);
}
extern "C" HANDLE CreateFileW(const wchar_t* path,DWORD access,DWORD share,void* security,DWORD creation,DWORD flags,HANDLE owner) {
    assert(access==GENERIC_READ && share==FILE_SHARE_READ && !security && creation==OPEN_EXISTING && !owner);
    assert(flags==(FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN));opened.emplace_back(path);
    if(opened.size()==fail_open_call || !disk.count(path))return INVALID_HANDLE_VALUE;
    auto value=std::make_unique<Handle>();value->bytes=disk.at(path);auto* p=value.get();handles.push_back(std::move(value));return p;
}
extern "C" int ReadFile(HANDLE p,void* out,DWORD extent,DWORD* count,void* overlapped) {
    assert(!overlapped && count);auto& h=handle(p);++h.reads;
    if(zero_read) { *count=0;return 0; }
    assert(h.position<=h.bytes.size());
    *count=std::min({extent,read_limit,static_cast<DWORD>(h.bytes.size()-h.position)});
    std::memcpy(out,h.bytes.data()+h.position,*count);h.position+=*count;return !false_read;
}
extern "C" int WriteFile(HANDLE,const void*,DWORD,DWORD*,void*) { assert(false);return 0; }
extern "C" int CloseHandle(HANDLE p) { auto& h=handle(p);++h.closes;return 1; }
extern "C" DWORD GetFileSize(HANDLE p,DWORD* high) { assert(!high);return handle(p).bytes.size(); }
extern "C" DWORD SetFilePointer(HANDLE p,LONG offset,LONG* high,DWORD origin) {
    assert(!high);auto& h=handle(p);
    if(origin==0)h.position=offset;else if(origin==FILE_CURRENT)h.position+=offset;
    else { assert(origin==FILE_END);h.position=h.bytes.size()+offset; }
    return h.position;
}
extern "C" DWORD GetCurrentDirectoryW(DWORD size,wchar_t* out) { assert(size==512);std::wcscpy(out,L"Z:\\game");return 7; }
extern "C" DWORD GetModuleFileNameW(HANDLE p,wchar_t* out,DWORD size) { assert(!p && size==260);std::wcscpy(out,L"Z:\\game\\th20.exe");return 16; }
extern "C" int MultiByteToWideChar(unsigned page,DWORD flags,const char* source,int size,wchar_t* out,int capacity) {
    assert(page==932 && flags==0 && size==-1 && capacity==260 && std::strlen(source)+1<=260);
    for(unsigned i=0;i<=std::strlen(source);++i) out[i]=static_cast<unsigned char>(source[i]);
    return std::strlen(source)+1;
}
extern "C" int wcscpy_s(wchar_t* out,std::size_t size,const wchar_t* source) { assert(std::wcslen(source)<size);std::wcscpy(out,source);return 0; }
extern "C" int wcscat_s(wchar_t* out,std::size_t size,const wchar_t* source) { assert(std::wcslen(out)+std::wcslen(source)<size);std::wcscat(out,source);return 0; }
extern "C" int strcpy_s(char* out,std::size_t size,const char* source) { assert(std::strlen(source)<size);std::strcpy(out,source);return 0; }
extern "C" int _stricmp(const char* a,const char* b) {
    for(;;++a,++b) { auto x=std::tolower(static_cast<unsigned char>(*a)),y=std::tolower(static_cast<unsigned char>(*b));if(x!=y || !x)return x-y; }
}
int main() {
    th20::DiagnosticAllocator allocator;th20::process_allocator=&allocator;
    std::vector<Member> members;
    for(unsigned i=0;i<8;++i)members.push_back({"entry"+std::to_string(i)+".dat",pattern(512,i+17),i==1});
    members.push_back({"entry0.dat",pattern(37,99),false});members.push_back({"zero.dat",{},false});
    disk[L"Z:\\game\\fixture.dat"]=archive(members);
    track_malloc=true;reset_failures();exercise_archive(members);exercise_failures();exercise_loose();
    archive_owner.close();assert(live_allocations()==0);
    for(const auto& h:handles)assert(h->closes==1);
    track_malloc=false;th20::process_allocator=nullptr;
    return 0;
}
