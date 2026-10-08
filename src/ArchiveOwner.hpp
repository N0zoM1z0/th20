#pragma once
#include "PbgFile.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstddef>
#include <cstring>

namespace th20 {
// Native four-word owners, sentinel record and catalog cursor. Nonvirtual
// spellings remain inferred; names use the C heap. A cursor word advance reads
// its new position even when the caller discards the result: guard is required.
struct ArchiveEntry {
    ArchiveEntry():name(nullptr),offset(0),decoded_size(0),field_0c(0) {}
    ~ArchiveEntry() { if (name) TH20_RELEASE_BYTES_AND_RESET(name); }
    char* name;
    std::int32_t offset,decoded_size,field_0c;
};
struct ArchiveCatalogCursor {
    char* pointer;
    std::uint32_t advance_word() { return *reinterpret_cast<std::uint32_t*>(pointer+=4); }
    char* advance_name() {
        std::int32_t size=std::strlen(pointer)+1;
        if (size%4) size+=4-size%4;
        return pointer+=size;
    }
};
struct ArchiveHeader { std::uint32_t magic; std::int32_t decoded_size,stored_size,count; };
struct ArchiveCipherParameters { std::uint8_t key,step;std::int32_t block,limit; };
extern ArchiveCipherParameters archive_member_parameters[8];
extern const char* archive_read_mode;
extern std::uint32_t archive_seek_start;
struct ArchiveOwner {
    ArchiveOwner():entries(nullptr),count(0),filename(nullptr),stream(nullptr) {}
    char* duplicate_name(const char* name);
    bool load_catalog(const char* name);
    void close();
    ArchiveEntry* parse_catalog(char*,std::int32_t,std::int32_t);
    ArchiveEntry* find(const char* name);
    std::uint8_t* read(const char* name,std::uint8_t* destination);
    std::int32_t size(const char* name);
    bool open(const char* name);
    ArchiveEntry* entries;
    std::int32_t count;
    char* filename;
    Pbg::File* stream;
};
extern ArchiveOwner archive_owner;

static_assert(sizeof(ArchiveHeader)==16);
static_assert(sizeof(ArchiveCipherParameters)==12);
static_assert(offsetof(ArchiveCipherParameters,block)==4);
static_assert(sizeof(void*)!=4 || sizeof(ArchiveEntry)==16);
static_assert(sizeof(void*)!=4 || sizeof(ArchiveOwner)==16);
static_assert(sizeof(void*)!=4 || sizeof(ArchiveCatalogCursor)==4);
} // namespace th20
