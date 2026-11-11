// Two original game-authored Card clock record-selector methods, 38B and
// 41B. Their 22B/20B indexed-array callees are compiler-style folded
// value accessors: the 22B physical head is already canonical and must
// not be credited again; the 20B head is a separate compiler helper.
#include "NativeCardClockViews.hpp"
#include <cstdint>
namespace th20 {
// The true contiguous 50-pointer region occupies +0x20 .. +0xE7.
// These borrowed views are never allocated and do not claim a larger owner.
struct NativeCardPointerSlots50 {
    std::uint8_t* entries[50];
    std::uint8_t*& at(std::int32_t index) {return entries[index];}
};
static_assert(sizeof(void*)!=4 || sizeof(NativeCardPointerSlots50)==0xC8);

// The genuine alternate records have a 44-byte element stride. Unknown
// record fields stay raw bytes; the original pointer at +0x10 is observed.
struct NativeCardRawRecord44 {std::uint8_t bytes[0x2C];};
struct NativeCardRawRecordArray {
    NativeCardRawRecord44 entries[5];
    NativeCardRawRecord44& at(std::int32_t index) {return entries[index];}
};
static_assert(sizeof(NativeCardRawRecord44)==0x2C);

std::uint8_t* NativeCardTimeSaveArchiveView::primary_record_488740(std::int32_t index) {
    auto& pointers=*reinterpret_cast<NativeCardPointerSlots50*>(
        reinterpret_cast<std::uint8_t*>(this)+0x20);
    return pointers.at(index);
}
std::uint8_t* NativeCardTimeSaveArchiveView::alternate_record_488770(std::int32_t index) {
    auto& records=*reinterpret_cast<NativeCardRawRecordArray*>(
        reinterpret_cast<std::uint8_t*>(this)+0xE8);
    return *reinterpret_cast<std::uint8_t**>(records.at(index).bytes+0x10);
}
}
