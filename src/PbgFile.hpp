#pragma once
#include <cstdint>
#include "Win32FileApi.hpp"

// Names and class tags are native RTTI evidence. Operation and field names,
// access visibility and original header spelling remain inferred.
namespace Pbg {
class IFile {
public:
    IFile();
    virtual bool open(const char*, const char*)=0;
    virtual void close()=0;
    virtual std::uint32_t read(void*, std::uint32_t)=0;
    virtual bool write(const void*, std::uint32_t)=0;
    virtual std::uint32_t position()=0;
    virtual std::uint32_t size()=0;
    virtual bool seek(std::int32_t, std::uint32_t)=0;
    virtual ~IFile();
};
class File : public IFile {
public:
    File();
    bool open(const char*, const char*) override;
    void close() override;
    std::uint32_t read(void*, std::uint32_t) override;
    bool write(const void*, std::uint32_t) override;
    std::uint32_t position() override;
    std::uint32_t size() override;
    bool seek(std::int32_t, std::uint32_t) override;
    ~File() override;
    HANDLE handle;
    DWORD access;
};
static_assert(sizeof(void*)!=4 || sizeof(File)==12);
// Native CP932/module-prefix conversion; failures retain the observed contract.
void convert_filename(wchar_t* destination,const char* name);
} // namespace Pbg
