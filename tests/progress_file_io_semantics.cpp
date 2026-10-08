#include "ProgressSaveManager.hpp"
#include "DiagnosticAllocator.hpp"
#include "DiagnosticLog.hpp"
#include "GameFileIo.hpp"
#include "EclFileLoader.hpp"
#include "ArchiveOwner.hpp"
#include "WideSecureCrt.hpp"
#include "Win32FileApi.hpp"
#include "SecureCrt.hpp"
#include "GameRandom.hpp"
#include "WindowState.hpp"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <map>
#include <memory>
#include <new>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
WindowState window_state{};
GameRandom progress_random(1);
std::uint32_t progress_spell_defaults[113];
DebugMemoryResource log_resource;
DiagnosticLog diagnostic_log{std::pmr::string(&log_resource),0};
void* game_file_handle;
ArchiveOwner archive_owner;
const char* archive_read_mode="r";
std::uint32_t archive_seek_start=0;
ArchiveCipherParameters archive_member_parameters[8]{}; // Archive mode is unused here.

}

namespace {
using namespace th20;
using Bytes=std::vector<std::uint8_t>;
struct Output {
    std::string name;
    Bytes bytes;
    bool closed=false;
    unsigned writes=0, closes=0;
    bool input=false;
    DWORD position=0;
};
std::vector<std::unique_ptr<Output>> handles;
std::map<std::string,Bytes> disk;
std::vector<std::string> reads, opens;
bool fail_open=false, short_first=false;
unsigned formatted=0, local_freed=0;
struct Allocations {
    std::vector<void*> pointers;
    std::vector<std::size_t> sizes, released;
};
Allocations* allocations=nullptr;

std::uint32_t step(std::uint32_t& state) {
    state=static_cast<std::uint64_t>(state)*48271%0x7fffffff;
    return state;
}
void initialize_records() {
    ProgressProfile profile;
    profile.field_0c=67; profile.field_10=71; profile.header.checksum=91;
    profile.spells[113].identifier=1234;
    profile.spells[0].captures[0]=39;
    profile.initialize();
    assert(profile.header.magic==0x5243 && profile.header.version==1 && profile.header.size==sizeof(profile));
    assert(profile.field_0c==67 && profile.field_10==71 && profile.header.checksum==91);
    for (unsigned difficulty=0; difficulty<7; ++difficulty) for (unsigned rank=0; rank<10; ++rank) {
        const auto& score=profile.scores[difficulty][rank];
        assert(score.score==100000-rank*10000 && score.stage==1 && score.continues==0);
        assert(score.timestamp==0 && score.slowdown==0 && std::strcmp(score.name,"--------")==0);
    }
    for (unsigned index=0; index<113; ++index)
        assert(profile.spells[index].identifier==index && profile.spells[index].default_value==progress_spell_defaults[index]);
    assert(profile.spells[113].identifier==1234 && profile.spells[0].captures[0]==39);

    ProgressMetadata metadata;
    metadata.field_60=123456; metadata.choices[5]=17; metadata.used_stones[3]=19;
    metadata.field_1d0=254;
    progress_random.seed(0x12345);
    std::uint32_t state=0x12345;
    std::array<std::uint8_t,32> first, second;
    for (auto& byte : first) byte=step(state)&255;
    for (auto& byte : second) byte=step(state)&255;
    const auto chosen_first=step(state)%32;
    const auto chosen_second=step(state)%32;
    ++first[chosen_first]; ++second[chosen_second];
    metadata.initialize();
    assert(metadata.header.magic==0x5453 && metadata.header.version==2 && metadata.header.size==sizeof(metadata));
    assert(std::strcmp(metadata.name,"        ")==0 && metadata.stones[8]==9);
    assert(std::equal(first.begin(),first.end(),metadata.salt_1b0));
    assert(std::equal(second.begin(),second.end(),metadata.salt_1d2));
    assert(progress_random.last==state && metadata.field_1d0==0);
    assert(metadata.field_60==123456 && metadata.choices[5]==17 && metadata.used_stones[3]==19);
    unsigned sum=0;
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(&metadata);
    for (unsigned index=0x58; index<0x1d0; ++index) sum+=bytes[index];
    assert(metadata.checksum==(sum&255) && metadata.calculate_integrity()==(sum&255));
}

ProgressSaveManager* make_owner() {
    // Zero backing storage is an explicit startup fixture, including padding.
    auto* memory=std::calloc(1,sizeof(ProgressSaveManager));
    assert(memory);
    auto* result=::new(memory) ProgressSaveManager;
    result->worker.close_and_join();
    return result;
}
void destroy_owner(ProgressSaveManager* owner) {
    owner->~ProgressSaveManager();
    std::free(owner);
}
void set_markers(ProgressSnapshot& snapshot, unsigned base) {
    for (unsigned character=0; character<2; ++character) for (unsigned index=0; index<9; ++index) {
        auto& profile=snapshot.profiles[character][index];
        profile.statistics.field_00=base+character*10+index;
        profile.field_0c=100; profile.field_10=101;
    }
    snapshot.fallback.statistics.field_00=base+90;
    snapshot.fallback.field_10=7;
    snapshot.metadata.field_60=base+100;
}
void check_markers(const ProgressSnapshot& snapshot, unsigned base) {
    for (unsigned character=0; character<2; ++character) for (unsigned index=0; index<9; ++index) {
        const auto& profile=snapshot.profiles[character][index];
        assert(profile.statistics.field_00==base+character*10+index);
        assert(profile.field_0c==character && profile.field_10==index);
    }
    assert(snapshot.fallback.statistics.field_00==base+90 && snapshot.fallback.field_0c==2);
    assert(snapshot.fallback.field_10==7 && snapshot.metadata.field_60==base+100);
}
void buffers_preserved(ProgressSnapshot& snapshot, const std::uint8_t* file,
                       const std::uint8_t* decoded, unsigned size) {
    assert(snapshot.file_buffer==file && snapshot.decoded_buffer==decoded && snapshot.file_size==size);
}
void exercise_files() {
    auto* owner=make_owner();
    assert(reads==std::vector<std::string>({"/cpu-score/scoreth20bak.dat","/cpu-score/scoreth20.dat"}));
    assert(owner->current.file_buffer && owner->backup.file_buffer);
    assert(owner->current.fallback.header.magic==0x5243);
    set_markers(owner->backup,700); set_markers(owner->current,900);
    // Disk checksums cover object representation, including native Profile
    // alignment bytes. Preserve those bytes through the actual value copy.
    auto& represented=owner->current.profiles[1][7];
    auto* representation=reinterpret_cast<std::uint8_t*>(&represented);
    for (unsigned index=0x14; index<0x18; ++index) representation[index]=0xa0+index;
    owner->save(nullptr);
    Bytes represented_bytes(sizeof(represented));
    std::memcpy(represented_bytes.data(),&represented,sizeof(represented));
    assert(opens==std::vector<std::string>({"/cpu-score/scoreth20bak.dat","/cpu-score/scoreth20.dat"}));
    check_markers(owner->current,900); check_markers(owner->backup,900);
    const auto original_disk=disk;
    assert(original_disk.size()==2);
    for (const auto& [name,packet] : original_disk) {
        (void)name;
        assert(packet.size()>44);
        ProgressFileHeader header;
        std::memcpy(&header,packet.data(),sizeof(header));
        assert(header.file_size==packet.size() && header.compressed_size==packet.size()-44);
        assert(header.decoded_size==19*sizeof(ProgressProfile)+sizeof(ProgressMetadata));
    }
    assert(handles.size()==2 && handles[0]->closed && handles[1]->closed);
    assert(handles[0]->writes==2 && handles[0]->closes==1);
    assert(game_file_handle==handles[1].get()); // Native close never clears it.

    // A non-CR slot is omitted from the real compressed/encrypted packet and
    // retains every byte through both writing and parsing the filtered file.
    auto& omitted=owner->current.profiles[1][8];
    omitted.header.magic=0x5858;
    omitted.header.checksum=0xdeadbeef;
    omitted.field_0c=41;
    omitted.field_10=43;
    Bytes omitted_bytes(sizeof(omitted));
    std::memcpy(omitted_bytes.data(),&omitted,sizeof(omitted));
    assert(owner->write("filtered.dat",&owner->current)==0);
    assert(std::memcmp(omitted_bytes.data(),&omitted,sizeof(omitted))==0);
    ProgressFileHeader filtered_header;
    const auto& filtered_packet=disk.at("/cpu-score/filtered.dat");
    std::memcpy(&filtered_header,filtered_packet.data(),sizeof(filtered_header));
    assert(filtered_header.file_size==filtered_packet.size());
    assert(filtered_header.compressed_size==filtered_packet.size()-sizeof(filtered_header));
    assert(filtered_header.decoded_size==18*sizeof(ProgressProfile)+sizeof(ProgressMetadata));
    assert(owner->current.decoded_buffer==nullptr);
    process_allocator->release_bytes(owner->current.file_buffer);
    std::int32_t filtered_size=0;
    owner->current.file_buffer=read_game_resource("/cpu-score/filtered.dat",&filtered_size,1);
    owner->current.file_size=filtered_size;
    assert(owner->parse(&owner->current)==0);
    assert(std::memcmp(omitted_bytes.data(),&omitted,sizeof(omitted))==0);
    assert(std::memcmp(represented_bytes.data(),&represented,sizeof(represented))==0);
    assert(represented.header.calculate_checksum(sizeof(represented))==represented.header.checksum);
    for (unsigned character=0; character<2; ++character) for (unsigned index=0; index<9; ++index) {
        if (character==1 && index==8) continue;
        const auto& profile=owner->current.profiles[character][index];
        assert(profile.statistics.field_00==900+character*10+index);
        assert(profile.field_0c==character && profile.field_10==index);
    }
    assert(owner->current.fallback.statistics.field_00==990 && owner->current.fallback.field_0c==2);
    assert(owner->current.metadata.field_60==1000);

    const auto* file=owner->current.file_buffer;
    const auto* decoded=owner->current.decoded_buffer;
    const auto file_size=owner->current.file_size;
    Allocations trace;
    allocations=&trace;
    fail_open=true;
    assert(owner->write("blocked.dat",&owner->current)==-1);
    allocations=nullptr;
    assert(trace.sizes.size()==2 && trace.sizes[0]==0x200000);
    const auto* header=reinterpret_cast<const ProgressFileHeader*>(owner->current.file_buffer);
    assert(trace.sizes[1]==2*header->decoded_size && trace.released==std::vector<std::size_t>({1,0}));
    buffers_preserved(owner->current,file,decoded,file_size);
    assert(formatted==1 && local_freed==1 && diagnostic_log.error==1);
    assert(diagnostic_log.text.find("error : ")==0 && diagnostic_log.text.back()=='\n');
    fail_open=false;

    const auto open_count=opens.size();
    auto* retained=owner->current.file_buffer;
    owner->current.file_buffer=nullptr;
    assert(owner->write("absent.dat",&owner->current)==-1 && opens.size()==open_count);
    owner->current.file_buffer=retained;
    short_first=true;
    assert(owner->write("short.dat",&owner->current)==0);
    assert(handles.back()->writes==2 && handles.back()->closes==3 && handles.back()->bytes.size()==43);
    assert(game_file_handle==handles.back().get());
    short_first=false;
    fail_open=true; // Actual destructor save cannot replace the captured files.
    destroy_owner(owner);
    fail_open=false;
    disk=original_disk; reads.clear();

    auto* restored=make_owner(); // Real load/defaults/parser/merge, with real encoded files.
    check_markers(restored->current,900); check_markers(restored->backup,900);
    assert(restored->current.decoded_buffer && restored->backup.decoded_buffer);
    assert(restored->current.file_size==disk.at("/cpu-score/scoreth20.dat").size());
    assert(restored->backup.file_size==disk.at("/cpu-score/scoreth20bak.dat").size());
    fail_open=true;
    destroy_owner(restored);
    fail_open=false;

    // A missing current file retains all records parsed from the older backup.
    disk=original_disk; disk.erase("/cpu-score/scoreth20.dat");
    auto* fallback=make_owner();
    check_markers(fallback->current,700); check_markers(fallback->backup,700);
    assert(fallback->current.decoded_buffer==nullptr && fallback->backup.decoded_buffer);
    fail_open=true;
    destroy_owner(fallback);
    fail_open=false;
}
} // namespace

extern "C" void* __real_malloc(std::size_t);
extern "C" void __real_free(void*);
extern "C" void* __wrap_malloc(std::size_t size) {
    // Heap-boundary fixture: native token fetch requires a readable guard byte
    // even though resource allocation requests exactly the file's logical size.
    auto* memory=__real_malloc(size+1);
    if (memory) static_cast<std::uint8_t*>(memory)[size]=0xff;
    if (allocations) { allocations->pointers.push_back(memory); allocations->sizes.push_back(size); }
    return memory;
}
extern "C" void __wrap_free(void* memory) {
    if (allocations) {
        const auto found=std::find(allocations->pointers.begin(),allocations->pointers.end(),memory);
        if (found!=allocations->pointers.end()) allocations->released.push_back(found-allocations->pointers.begin());
    }
    __real_free(memory);
}
extern "C" int strcpy_s(char* destination, std::size_t size, const char* source) {
    assert(std::strlen(source)<size);
    std::memcpy(destination,source,std::strlen(source)+1);
    return 0;
}
extern "C" int vsprintf_s(char* buffer, std::size_t size, const char* format, std::va_list arguments) {
    const auto result=std::vsnprintf(buffer,size,format,arguments);
    assert(result>=0 && static_cast<std::size_t>(result)<size);
    return result;
}
extern "C" HANDLE CreateFileW(const wchar_t* name, DWORD access, DWORD sharing,
                               void* security, DWORD creation, DWORD attributes, HANDLE existing) {
    assert(sharing==FILE_SHARE_READ && !security && !existing);
    const bool input=access==GENERIC_READ;
    if (input) assert(creation==OPEN_EXISTING && attributes==(FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN));
    else assert(access==GENERIC_WRITE && creation==CREATE_ALWAYS && attributes==FILE_ATTRIBUTE_NORMAL);
    std::string filename;
    for (; *name; ++name) { assert(*name>0 && *name<128); filename+=static_cast<char>(*name); }
    if (input) {
        reads.push_back(filename);
        if (disk.find(filename)==disk.end()) return INVALID_HANDLE_VALUE;
    } else {
        opens.push_back(filename);
        if (fail_open) return INVALID_HANDLE_VALUE;
    }
    handles.push_back(std::make_unique<Output>());
    handles.back()->name=filename;
    handles.back()->input=input;
    if (input) handles.back()->bytes=disk.at(filename);
    else disk[filename].clear();
    return handles.back().get();
}
extern "C" int WriteFile(HANDLE handle, const void* bytes, DWORD size, DWORD* written, void* overlapped) {
    assert(!overlapped);
    auto& output=*static_cast<Output*>(handle);
    ++output.writes;
    if (output.closed) { *written=0; return 0; }
    *written=short_first && output.writes==1 ? size-1 : size;
    const auto* first=static_cast<const std::uint8_t*>(bytes);
    output.bytes.insert(output.bytes.end(),first,first+*written);
    disk[output.name]=output.bytes;
    return 1;
}
extern "C" int CloseHandle(HANDLE handle) {
    auto& output=*static_cast<Output*>(handle);
    ++output.closes;
    const bool success=!output.closed;
    output.closed=true;
    return success;
}
extern "C" DWORD GetLastError() { return 5; }
extern "C" DWORD FormatMessageW(DWORD flags, const void* source, DWORD error, DWORD language,
                                LPWSTR output, DWORD capacity, void* arguments) {
    assert(flags==0x1300 && !source && error==5 && language==0x400 && capacity==0 && !arguments);
    auto** message=reinterpret_cast<wchar_t**>(output);
    *message=new wchar_t[7]{L'd',L'e',L'n',L'i',L'e',L'd',0};
    ++formatted;
    return 6;
}
extern "C" void* LocalFree(void* memory) {
    ++local_freed;
    delete[] static_cast<wchar_t*>(memory);
    return nullptr;
}
// OS/CRT boundary fixtures for the genuine shared resource and File bodies.
extern "C" int ReadFile(HANDLE handle, void* destination, DWORD size, DWORD* count, void* overlapped) {
    assert(!overlapped);
    auto& input=*static_cast<Output*>(handle);
    assert(input.input && !input.closed && input.position<=input.bytes.size());
    *count=std::min(size,static_cast<DWORD>(input.bytes.size()-input.position));
    std::memcpy(destination,input.bytes.data()+input.position,*count);
    input.position+=*count;
    return 1;
}
extern "C" DWORD GetFileSize(HANDLE handle,DWORD* high) {
    assert(!high);auto& input=*static_cast<Output*>(handle);
    assert(input.input && !input.closed);return input.bytes.size();
}
extern "C" DWORD SetFilePointer(HANDLE handle,LONG offset,LONG* high,DWORD origin) {
    assert(!high);auto& input=*static_cast<Output*>(handle);assert(!input.closed);
    if (!origin) input.position=offset;
    else if (origin==FILE_CURRENT) input.position+=offset;
    else { assert(origin==FILE_END);input.position=input.bytes.size()+offset; }
    return input.position;
}
extern "C" DWORD GetCurrentDirectoryW(DWORD size,wchar_t* output) {
    assert(size>=11);std::wcscpy(output,L"/cpu-score");return 10;
}
extern "C" DWORD GetModuleFileNameW(HANDLE module,wchar_t* output,DWORD size) {
    assert(!module && size==260);std::wcscpy(output,L"Z:\\game\\th20.exe");return 16;
}
extern "C" int MultiByteToWideChar(unsigned page,DWORD flags,const char* source,int size,wchar_t* output,int capacity) {
    assert(page==932 && !flags && size==-1 && capacity==260);
    const auto extent=std::strlen(source);assert(extent+1<=static_cast<unsigned>(capacity));
    for (unsigned i=0;i<=extent;++i) output[i]=static_cast<unsigned char>(source[i]);
    return extent+1;
}
extern "C" int wcscpy_s(wchar_t* output,std::size_t size,const wchar_t* source) {
    assert(std::wcslen(source)<size);std::wcscpy(output,source);return 0;
}
extern "C" int wcscat_s(wchar_t* output,std::size_t size,const wchar_t* source) {
    assert(std::wcslen(output)+std::wcslen(source)<size);std::wcscat(output,source);return 0;
}
extern "C" int _stricmp(const char* left,const char* right) {
    for (;;++left,++right) {
        const auto a=std::tolower(static_cast<unsigned char>(*left)),b=std::tolower(static_cast<unsigned char>(*right));
        if (a!=b || !a) return a-b;
    }
}

int main() {
    th20::DiagnosticAllocator allocator;
    th20::process_allocator=&allocator;
    th20::game_file_handle=INVALID_HANDLE_VALUE;
    assert(th20::close_game_output()==0 && th20::write_game_output(nullptr,0)==-1);
    std::strcpy(th20::window_state.user_data_directory,"/cpu-score");
    for (unsigned index=0; index<113; ++index) th20::progress_spell_defaults[index]=7000+index*19;
    initialize_records();
    exercise_files();
    th20::diagnostic_log.text.clear();
    const char format[]="%s:%d";
    assert(th20::report_log_error(&th20::diagnostic_log,format,"probe",23)==format);
    assert(th20::diagnostic_log.text=="probe:23" && th20::diagnostic_log.error==1);
    th20::process_allocator=nullptr;
}
