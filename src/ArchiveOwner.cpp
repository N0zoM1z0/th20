#include "ArchiveOwner.hpp"
#include "ArchiveCrypt.hpp"
#include "ArchiveLzss.hpp"
#include "EclDiagnostic.hpp"
#include "SecureCrt.hpp"
#include "CaseInsensitiveCrt.hpp"

namespace th20 {
char* ArchiveOwner::duplicate_name(const char* name) {
    std::int32_t size=std::strlen(name)+1;
    auto* copy=static_cast<char*>(process_allocator->allocate_bytes(size,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\_ArcMngr.cpp:422 char"));
    if (copy) strcpy_s(copy,std::strlen(name)+1,name);
    return copy;
}

bool ArchiveOwner::load_catalog(const char* name) {
    ArchiveHeader header;
    std::uint8_t* stored=nullptr;
    std::uint8_t* decoded=nullptr;
    std::int32_t extent,catalog_offset;
    if (!stream) return false;
    if (!stream->open(name,archive_read_mode)) goto fail;
    if (!stream->read(&header,sizeof(header))) goto fail;
    archive_decrypt(reinterpret_cast<std::uint8_t*>(&header),sizeof(header),0x1b,0x37,16,16);
    if (header.magic!=0x31414854) goto fail;
    header.decoded_size-=123456789;
    header.stored_size-=987654321;
    count=header.count-135792468;
    extent=stream->size();
    catalog_offset=extent-header.stored_size;
    stream->seek(catalog_offset,archive_seek_start);
    extent=header.stored_size;
    stored=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(extent,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\_ArcMngr.cpp:344 void"));
    if (!stored) goto fail;
    if (!stream->read(stored,extent)) goto fail;
    archive_decrypt(stored,extent,0x3e,0x9b,0x80,extent);
    decoded=archive_decompress(stored,extent,nullptr,header.decoded_size);
    if (!decoded) goto fail;
    entries=parse_catalog(reinterpret_cast<char*>(decoded),count,catalog_offset);
    if (!entries) goto fail;
    TH20_RELEASE_BYTES_AND_RESET(stored);
    TH20_RELEASE_BYTES_AND_RESET(decoded);
    return true;
fail:
    TH20_RELEASE_BYTES_AND_RESET(stored);
    TH20_RELEASE_BYTES_AND_RESET(decoded);
    process_allocator->release_object(stream);stream=nullptr;
    return false;
}
void ArchiveOwner::close() {
    if (filename) {
        ecl_diagnostic_hint("info : %s close arcfile\r\n",filename);
        TH20_RELEASE_BYTES_AND_RESET(filename);
    }
    filename=nullptr;
    TH20_RELEASE_ARRAY_AND_RESET(entries);
    process_allocator->release_object(stream);stream=nullptr;
    count=0;
}
ArchiveEntry* ArchiveOwner::parse_catalog(char* bytes,std::int32_t size,std::int32_t end) {
    ArchiveEntry* result=nullptr;
    result=process_allocator->allocate_array<ArchiveEntry>("D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\_ArcMngr.cpp:385 ARCFILE_INFO",size+1);
    if (!result) goto fail;
    {
        ArchiveCatalogCursor cursor{bytes};
        for (std::int32_t index=0;index<size;++index) {
            result[index].name=duplicate_name(cursor.pointer);
            cursor.advance_name();
            result[index].offset=*reinterpret_cast<std::int32_t*>(cursor.pointer);
            cursor.advance_word();
            result[index].decoded_size=*reinterpret_cast<std::int32_t*>(cursor.pointer);
            cursor.advance_word();
            result[index].field_0c=*reinterpret_cast<std::int32_t*>(cursor.pointer);
            cursor.advance_word();
        }
    }
    result[size].offset=end;
    result[size].decoded_size=0;
    return result;
fail:
    if (result) { delete[] result;result=nullptr; }
    return nullptr;
}
ArchiveEntry* ArchiveOwner::find(const char* name) {
    if (!entries) return nullptr;
    auto* entry=entries;
    std::int32_t remaining=count;
    for (;remaining>0;--remaining,++entry) {
        if (!_stricmp(name,entry->name)) return entry;
    }
    return nullptr;
}
std::uint8_t* ArchiveOwner::read(const char* name,std::uint8_t* destination) {
    std::uint8_t* stored=nullptr;
    std::uint8_t parameter=0;
    ArchiveEntry* entry;
    std::int32_t extent,decoded_size;
    std::uint8_t* result;
    if (!stream) return nullptr;
    entry=find(name);
    if (!entry) goto fail;
    extent=entry[1].offset-entry[0].offset;
    decoded_size=entry->decoded_size;
    if (extent!=decoded_size || !destination) {
        stored=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(extent,"D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\_ArcMngr.cpp:173 BYTE"));
        if (!stored) goto fail;
    } else stored=destination;
    if (!stream->seek(entry[0].offset,archive_seek_start)) goto fail;
    if (!stream->read(stored,extent)) goto fail;
    parameter=archive_name_sum(entry[0].name,std::strlen(entry[0].name))%8;
    archive_decrypt(stored,extent,archive_member_parameters[parameter].key,archive_member_parameters[parameter].step,
        archive_member_parameters[parameter].block,archive_member_parameters[parameter].limit);
    if (extent!=decoded_size) result=archive_decompress(stored,extent,destination,decoded_size);
    else result=stored;
    if (stored!=destination) { if (stored) TH20_RELEASE_BYTES_AND_RESET(stored); }
    return result;
fail:
    ecl_diagnostic_hint("info : %s error\r\n",filename);
    if (stored) TH20_RELEASE_BYTES_AND_RESET(stored);
    return nullptr;
}
std::int32_t ArchiveOwner::size(const char* name) {
    auto* entry=find(name);
    if (entry) { return entry->decoded_size; }
    else { return 0; }
}
bool ArchiveOwner::open(const char* name) {
    close();
    wchar_t directory[512];
    GetCurrentDirectoryW(512,directory);
    ecl_diagnostic_hint("info : CurrentDirectory %s \r\n",directory);
    ecl_diagnostic_hint("info : %s open arcfile\r\n",name);
    stream=process_allocator->allocate_object<Pbg::File>("D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\_ArcMngr.cpp:78 File");
    if (!stream) return false;
    if (load_catalog(name)) {
        filename=duplicate_name(name);
        if (filename) {
            stream->open(filename,archive_read_mode);
            return true;
        }
    }
    ecl_diagnostic_hint("info : %s not found\r\n",name);
    close();
    return false;
}
} // namespace th20
