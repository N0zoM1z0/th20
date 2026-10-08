#include "ArchiveCrypt.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstring>

namespace th20 {

std::uint8_t archive_name_sum(const char* name, std::uint32_t size) {
    const char* cursor = name;
    std::uint8_t sum = 0;
    while (size--) {
        sum = static_cast<std::uint8_t>(sum + static_cast<std::uint8_t>(*cursor));
        ++cursor;
    }
    return sum;
}

const char crypt_copy_label[] = "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\filectrl.cpp:50 u_char";

std::uint8_t* archive_decrypt(std::uint8_t* data, std::int32_t size,
    std::uint8_t key, std::uint8_t step, std::int32_t block, std::int32_t limit) {
    std::int32_t tail = size % block < block / 4 ? size % block : 0;
    std::int32_t copy_size = limit > size ? size : limit;
    std::uint8_t* cursor = data;
    std::uint8_t* input = process_allocator->allocate_array<std::uint8_t>(crypt_copy_label, copy_size);
    std::uint8_t* owned_copy = input;
    tail += size & 1;
    size -= tail;
    std::memcpy(input, data, copy_size);
    while (size > 0 && limit > 0) {
        if (size < block) block = size;
        std::uint8_t* block_start = cursor;
        cursor += block - 1;
        std::int32_t half;
        for (half = (block + 1) / 2; half > 0; --half, ++input) {
            *cursor = *input ^ key;
            cursor -= 2;
            key = key + step;
        }
        cursor = block_start + block - 2;
        for (half = block / 2; half > 0; --half, ++input) {
            *cursor = *input ^ key;
            cursor -= 2;
            key = key + step;
        }
        size -= block;
        cursor = block_start + block;
        limit -= block;
    }
    TH20_RELEASE_ARRAY_AND_RESET(owned_copy);
    return data;
}

const char encrypt_copy_label[] = "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\filectrl.cpp:131 u_char";

std::uint8_t* archive_encrypt(std::uint8_t* data, std::int32_t size,
    std::uint8_t key, std::uint8_t step, std::int32_t block, std::int32_t limit) {
    std::int32_t tail = size % block < block / 4 ? size % block : 0;
    std::int32_t copy_size = limit > size ? size : limit;
    std::uint8_t* cursor = data;
    std::uint8_t* input = process_allocator->allocate_array<std::uint8_t>(encrypt_copy_label, copy_size);
    std::uint8_t* owned_copy = input;
    tail += size & 1;
    size -= tail;
    std::memcpy(input, data, copy_size);
    while (size > 0 && limit > 0) {
        if (size < block) block = size;
        std::uint8_t* block_start = input;
        input += block - 1;
        std::int32_t half;
        for (half = (block + 1) / 2; half > 0; --half, ++cursor) {
            *cursor = *input ^ key;
            input -= 2;
            key = key + step;
        }
        input = block_start + block - 2;
        for (half = block / 2; half > 0; --half, ++cursor) {
            *cursor = *input ^ key;
            input -= 2;
            key = key + step;
        }
        size -= block;
        input = block_start + block;
        limit -= block;
    }
    TH20_RELEASE_ARRAY_AND_RESET(owned_copy);
    return data;
}


} // namespace th20
