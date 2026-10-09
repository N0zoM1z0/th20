#include "SoundInf.hpp"
#include "SoundDeviceOwner.hpp"
#include "Graphics.hpp"
#include "DiagnosticAllocator.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <limits>
#include <memory_resource>
#include <string>
#include <thread>
#include <vector>

// Explicit unresolved startup bindings. These are owned fixture objects, not
// native startup or resource-owning destruction implementations. Real member
// constructors, PMR containers, guards, allocator and loading bodies execute.
namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator = &allocator;
Graphics::~Graphics() = default; // Fixture has no graphics resources or tasks.
Graphics process_graphics;
SoundInf::SoundInf() noexcept {} // Original definition binding remains open.
SoundInf process_sound;
SoundDeviceOwner::SoundDeviceOwner() : direct_sound(nullptr) {}
SoundDeviceOwner::~SoundDeviceOwner() = default; // No owned COM fixture object.
DWORD sound_notification_thread(void*) { std::abort(); } // Must remain uncalled.
}

namespace {
using namespace th20;
int file_token, event_token, thread_token, window_token, stream_token, ds_token;
std::vector<const char*> events;
std::vector<std::string> messages;
bool file_failure, allocation_failure, read_failure, event_failure, thread_failure;
bool conversion_failure, seek_failure;
DWORD read_limit = std::numeric_limits<DWORD>::max();
HRESULT factory_status;
int lookup_index, reopen_status;
SoundInf* lookup_receiver;
SoundInf* reopen_receiver;
std::string lookup_name, reopened_name;
void* allocated[64]{};
std::size_t allocation_sizes[64]{};
unsigned allocated_count, freed_count, closed_files;
struct FactoryObservation {
    SoundDeviceOwner* receiver;
    StreamingSound** output;
    BYTE* bytes;
    ULONG size;
    TrackFormat* format;
    DWORD flags;
    GUID guid;
    DWORD count, stride;
    HANDLE notification;
} factory{};

void reset_calls() {
    events.clear(); messages.clear(); lookup_name.clear(); reopened_name.clear();
    lookup_receiver = reopen_receiver = nullptr;
    file_failure = allocation_failure = read_failure = event_failure = thread_failure = false;
    conversion_failure = seek_failure = false;
    read_limit = std::numeric_limits<DWORD>::max();
    factory_status = 0; lookup_index = 0; reopen_status = 0; factory = {};
    assert(allocated_count == freed_count);
    allocated_count = freed_count = closed_files = 0;
}
void expect_calls(std::initializer_list<const char*> expected) {
    assert(events.size() == expected.size());
    assert(std::equal(events.begin(), events.end(), expected.begin(),
        [](const char* a, const char* b) { return std::strcmp(a,b) == 0; }));
}
void assert_slot_available(unsigned slot) {
    // A recursive same-thread try_lock would not detect a leaked guard.
    bool acquired = false;
    std::thread observer([&] {
        auto& mutex = process_locks.slot(slot);
        acquired = mutex.try_lock();
        if (acquired) mutex.unlock();
    });
    observer.join(); assert(acquired);
}
struct ThrowingResource : std::pmr::memory_resource {
    bool fail = true;
    unsigned allocations = 0, deallocations = 0;
    void* do_allocate(std::size_t n, std::size_t a) override {
        ++allocations;
        if (fail) throw std::bad_alloc();
        return std::pmr::new_delete_resource()->allocate(n,a);
    }
    void do_deallocate(void* p, std::size_t n, std::size_t a) override {
        ++deallocations; std::pmr::new_delete_resource()->deallocate(p,n,a);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
struct DefaultResourceScope {
    std::pmr::memory_resource* previous;
    explicit DefaultResourceScope(std::pmr::memory_resource* r)
        : previous(std::pmr::set_default_resource(r)) {}
    ~DefaultResourceScope() { std::pmr::set_default_resource(previous); }
};
void configure(SoundInf& sound, SoundDeviceOwner& owner, TrackFormat* formats) {
    sound.device_owner = &owner;
    sound.direct_sound = reinterpret_cast<IDirectSound8*>(&ds_token);
    sound.track_formats = formats;
    std::strcpy(sound.music_file, "fixture.dat");
    process_graphics.configuration.flags.preload_music = 1;
    process_graphics.configuration.value_75 = 1;
    process_graphics.window_handle = &window_token;
}
TrackFormat make_format(const char* name, DWORD offset, DWORD count) {
    TrackFormat t{}; std::strcpy(t.name,name);
    t.file_offset=offset; t.preload_bytes=count;
    t.format.nSamplesPerSec=44100; t.format.nBlockAlign=4;
    return t;
}
void check_factory(SoundInf& sound, SoundDeviceOwner& owner, int index) {
    const auto& p=sound.preloaded[index];
    // Wide arithmetic plus explicit truncation is independent of the loading
    // body's uint32 multiply/shift expression, including wraparound cases.
    std::uint64_t product = std::uint64_t(p.format->format.nSamplesPerSec)*4*
        p.format->format.nBlockAlign;
    DWORD wrapped = static_cast<DWORD>(product % (std::uint64_t(1)<<32));
    DWORD units = (wrapped / 16) / p.format->format.nBlockAlign;
    DWORD expected = units * p.format->format.nBlockAlign;
    assert(factory.receiver==&owner && factory.output==&sound.stream);
    assert(factory.bytes==p.current && factory.size==p.size && factory.format==p.format);
    assert(factory.flags==0x10100 && factory.count==16 && factory.stride==expected);
    const GUID zero{}; assert(std::memcmp(&factory.guid,&zero,sizeof zero)==0);
    assert(factory.notification==sound.notification);
}
}

extern "C" const GUID GUID_NULL{};
extern "C" void* __real_malloc(std::size_t);
extern "C" void __real_free(void*);
extern "C" void* __wrap_malloc(std::size_t n) {
    events.push_back("allocate");
    if (allocation_failure) return nullptr;
    assert(allocated_count<64);
    void* p=__real_malloc(n); assert(p);
    // A sentinel is fixture instrumentation, not native zero-fill policy.
    std::memset(p,0xa5,n);
    allocated[allocated_count]=p; allocation_sizes[allocated_count++]=n;
    return p;
}
extern "C" void __wrap_free(void* p) {
    assert(p); events.push_back("free");
    unsigned i=0;
    while (i<allocated_count && allocated[i]!=p) ++i;
    assert(i<allocated_count); allocated[i]=nullptr; ++freed_count;
    __real_free(p);
}
extern "C" int strcpy_s(char* output, std::size_t size, const char* input) {
    assert(output && input && std::strlen(input)<size);
    std::memcpy(output,input,std::strlen(input)+1); return 0;
}
extern "C" int MultiByteToWideChar(unsigned page,DWORD flags,const char* input,
    int length,wchar_t* output,int capacity) {
    events.push_back("convert");
    assert(page==932 && flags==0 && length==-1 && capacity==260);
    assert(std::strcmp(input,"fixture.dat")==0);
    for (int i=0;i<=capacity;++i) assert(output[i]==0); // Actual 261-element buffer.
    if (conversion_failure) return 0;
    for (std::size_t i=0;i<=std::strlen(input);++i) output[i]=input[i];
    return static_cast<int>(std::strlen(input)+1);
}
extern "C" HANDLE CreateFileW(const wchar_t* name,DWORD access,DWORD share,
    void* security,DWORD mode,DWORD flags,HANDLE template_file) {
    events.push_back("open");
    assert(std::wcscmp(name,conversion_failure ? L"" : L"fixture.dat")==0);
    assert(access==0x80000000 && share==1 && !security && mode==3);
    assert(flags==0x08000080 && !template_file);
    return file_failure ? INVALID_HANDLE_VALUE : &file_token;
}
extern "C" DWORD SetFilePointer(HANDLE file,LONG distance,LONG* high,DWORD method) {
    events.push_back("seek"); assert(file==&file_token && !high && method==0);
    assert(lookup_receiver && static_cast<DWORD>(distance)==
        lookup_receiver->track_formats[lookup_index].file_offset);
    return seek_failure ? 0xffffffffu : static_cast<DWORD>(distance);
}
extern "C" int ReadFile(HANDLE file,void* output,DWORD count,DWORD* read,void* overlapped) {
    events.push_back("read"); assert(file==&file_token && read && !overlapped);
    assert(allocated_count && output==allocated[allocated_count-1]);
    assert(count==allocation_sizes[allocated_count-1]);
    DWORD copied=std::min(count,read_limit);
    for (DWORD i=0;i<copied;++i) static_cast<BYTE*>(output)[i]=static_cast<BYTE>(i*7+3);
    *read=copied;
    return !read_failure;
}
extern "C" int CloseHandle(HANDLE h) {
    assert(h==&file_token); events.push_back("close_file"); ++closed_files; return 1;
}
extern "C" HANDLE CreateEventW(void* security,BOOL manual,BOOL initial,const wchar_t* name) {
    events.push_back("event"); assert(!security && !manual && !initial && !name);
    return event_failure ? nullptr : &event_token;
}
extern "C" HANDLE CreateThread(void* security,std::size_t stack,DWORD (*fn)(void*),
    void* argument,DWORD flags,DWORD* id) {
    events.push_back("thread");
    assert(!security && !stack && fn==sound_notification_thread);
    assert(argument==&window_token && !flags && id);
    if (thread_failure) return nullptr;
    *id=0x76543210; return &thread_token;
}
namespace th20 {
void sound_log(const char* format,...) {
    std::va_list args; va_start(args,format); char buffer[512];
    int size=std::vsnprintf(buffer,sizeof buffer,format,args); va_end(args);
    assert(size>=0 && size<512); messages.emplace_back(buffer);
}
std::int32_t SoundInf::find_track(const char* name) {
    events.push_back("find"); lookup_receiver=this; lookup_name=name;
    return lookup_index; // Lookup/locale/invalid-name implementation remains open.
}
std::int32_t SoundInf::reopen_track(const char* name) {
    events.push_back("reopen"); reopen_receiver=this; reopened_name=name;
    return reopen_status; // Original stream/base ownership remains open.
}
HRESULT SoundDeviceOwner::create_memory_stream(StreamingSound** output,BYTE* bytes,
    ULONG size,TrackFormat* format,DWORD flags,GUID guid,DWORD count,DWORD stride,HANDLE event) {
    events.push_back("factory");
    factory={this,output,bytes,size,format,flags,guid,count,stride,event};
    if (factory_status>=0) *output=reinterpret_cast<StreamingSound*>(&stream_token);
    return factory_status; // Original SDK/COM factory body remains undefined.
}
}

int main() {
    using namespace th20;
    SoundDeviceOwner owner;
    TrackFormat formats[]={make_format("first",123,32),make_format("second",456,64)};
    SoundInf sound; configure(sound,owner,formats);

    // Preload grows/value-initializes before global name publication and gating.
    reset_calls(); process_graphics.configuration.flags.preload_music=0;
    assert(sound.preload(15,"disabled")==0 && sound.preloaded.size()==16);
    expect_calls({}); assert(std::strcmp(process_sound.track_names[15],"disabled")==0);
    assert(sound.track_names[15][0]==0);
    for (const auto& p:sound.preloaded)
        assert(!p.format && !p.allocation && !p.current && !p.size);
    process_graphics.configuration.flags.preload_music=1;
    sound.device_owner=nullptr;
    assert(sound.preload(3,"no-device")==0); expect_calls({});
    assert(std::strcmp(process_sound.track_names[3],"no-device")==0);
    sound.device_owner=&owner;

    // Resize's actual PMR exception is before publication; guard must unwind.
    reset_calls(); ThrowingResource resource;
    {
        DefaultResourceScope scope(&resource); SoundInf throwing;
        configure(throwing,owner,formats);
        std::strcpy(process_sound.track_names[14],"unchanged");
        try { throwing.preload(14,"would-grow"); assert(false); }
        catch (const std::bad_alloc&) {}
        assert(throwing.preloaded.empty() && resource.allocations==1);
        assert(std::strcmp(process_sound.track_names[14],"unchanged")==0);
        expect_calls({}); assert_slot_available(2);
        resource.fail=false; process_graphics.configuration.flags.preload_music=0;
        assert(throwing.preload(14,"now-grown")==0 && throwing.preloaded.size()==15);
    }
    assert(resource.deallocations==1);
    process_graphics.configuration.flags.preload_music=1;

    // Native ignores conversion/seek/short read/BOOL statuses, publishes the
    // requested size, and does not initialize unfilled allocation bytes.
    for (unsigned scenario=0;scenario<4;++scenario) {
        reset_calls(); lookup_index=scenario%2;
        conversion_failure=scenario==1; seek_failure=scenario==2;
        read_limit=scenario==0 ? 32 : 5; read_failure=scenario==3;
        assert(sound.preload(2,"first")==0);
        expect_calls({"convert","open","find","seek","allocate","read","close_file"});
        auto& p=sound.preloaded[2]; const auto& format=formats[lookup_index];
        assert(lookup_receiver==&sound && lookup_name=="first" && closed_files==1);
        assert(p.format==&formats[lookup_index] && p.current==p.allocation && p.size==format.preload_bytes);
        for (DWORD i=0;i<p.size;++i)
            assert(p.allocation[i]==(i<std::min(p.size,read_limit) ? static_cast<BYTE>(i*7+3) : 0xa5));
        std::strcpy(sound.track_names[2],"first");
        events.clear(); messages.clear();
        std::strcpy(process_sound.track_names[2],"global-sentinel");
        assert(sound.preload(2,"first")==0); expect_calls({}); assert(messages.empty());
        assert(std::strcmp(process_sound.track_names[2],"global-sentinel")==0);
        auto* retained=p.current; sound.free_preload(2);
        expect_calls({"free"}); assert(!p.allocation && p.current==retained && p.format==&formats[lookup_index]);
        assert(p.size==format.preload_bytes && allocated_count==freed_count);
        events.clear(); sound.free_preload(2); expect_calls({});
    }

    // Failed replacement frees its old allocation but retains the other three
    // record fields, with global name already changed and no invented rollback.
    for (unsigned failure=0;failure<2;++failure) {
        reset_calls(); assert(sound.preload(1,"first")==0);
        auto prior=sound.preloaded[1]; std::strcpy(sound.track_names[1],"first");
        events.clear(); messages.clear(); file_failure=failure==0; allocation_failure=failure==1;
        assert(sound.preload(1,"second")==-1);
        if (!failure) expect_calls({"free","convert","open"});
        else expect_calls({"free","convert","open","find","seek","allocate","close_file"});
        assert(std::strcmp(process_sound.track_names[1],"second")==0);
        auto& p=sound.preloaded[1]; assert(!p.allocation && p.current==prior.current && p.format==prior.format && p.size==prior.size);
        assert(allocated_count==freed_count); assert_slot_available(1); assert_slot_available(2);
        assert(messages.size()==2 && messages.back()=="error : bgmfile is not find fixture.dat\r\n");
    }

    // Early loading gates precede reopen/resize and do not change handles/name.
    reset_calls(); std::strcpy(sound.track_names[4],"reopen-name");
    std::strcpy(sound.current_track,"retained-current");
    sound.device_owner=nullptr; assert(sound.load_track(4)==-1); expect_calls({});
    sound.device_owner=&owner; process_graphics.configuration.value_75=0;
    assert(sound.load_track(4)==-1); expect_calls({});
    process_graphics.configuration.value_75=1; sound.direct_sound=nullptr;
    assert(sound.load_track(4)==-1); expect_calls({});
    sound.direct_sound=reinterpret_cast<IDirectSound8*>(&ds_token);
    process_graphics.configuration.flags.preload_music=0; reopen_status=-1;
    assert(sound.load_track(4)==-1); expect_calls({"reopen"});
    assert(reopen_receiver==&sound && reopened_name=="reopen-name");
    events.clear(); reopen_status=0; assert(sound.load_track(4)==0); expect_calls({"reopen"});
    assert(std::strcmp(sound.current_track,"retained-current")==0);
    process_graphics.configuration.flags.preload_music=1;
    reset_calls(); SoundInf empty; configure(empty,owner,formats);
    assert(empty.load_track(15)==-1 && empty.preloaded.size()==16); expect_calls({});

    reset_calls(); assert(sound.preload(5,"first")==0);
    std::strcpy(sound.track_names[5],"first");
    // Factory has no real stream object here: the resulting token is never
    // dereferenced, and captures prove only this caller's protocol.
    unsigned loading_checks=0;
    for (DWORD rate:std::array<DWORD,7>{0,1,44100,192000,0x40000000u,0x80000001u,0xffffffffu})
        for (std::uint16_t align:std::array<std::uint16_t,5>{1,3,4,8191,65535})
            for (unsigned failure=0;failure<4;++failure) {
                events.clear(); messages.clear();
                sound.preloaded[5].format->format.nSamplesPerSec=rate;
                sound.preloaded[5].format->format.nBlockAlign=align;
                sound.preloaded[5].current=sound.preloaded[5].allocation+2;
                sound.preloaded[5].size=7;
                sound.preloaded_index=13; sound.notify_thread_id=0x11111111;
                sound.stream=nullptr;
                event_failure=failure==1; thread_failure=failure==2;
                factory_status=failure==3 ? std::numeric_limits<HRESULT>::min() : 1;
                int result=sound.load_track(5);
                expect_calls({"event","thread","factory"}); check_factory(sound,owner,5);
                assert(sound.notification==(event_failure ? nullptr : &event_token));
                assert(sound.notify_thread==(thread_failure ? nullptr : &thread_token));
                assert(sound.notify_thread_id==(thread_failure ? 0x11111111 : 0x76543210));
                assert(std::strcmp(sound.current_track,"first")==0);
                if (factory_status<0) {
                    assert(result==-1 && sound.preloaded_index==13 && !sound.stream);
                    assert(messages.size()==2 && messages[1].find("error : ")==0);
                } else {
                    assert(result==0 && sound.preloaded_index==5);
                    assert(sound.stream==reinterpret_cast<StreamingSound*>(&stream_token));
                    assert(messages.size()==2 && messages.back()=="load comp\r\n");
                }
                ++loading_checks;
            }
    sound.free_preload(5); assert(allocated_count==freed_count);
    std::printf("Whole shared sound loading: %u notification/failure cases; preload, replacement, PMR unwind and resource protocol PASS\n",loading_checks);
}
