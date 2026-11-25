#pragma once

#include <cstddef>

static_assert(offsetof(th20::AnimationFlags, word_10) == 0x10);
static_assert(offsetof(th20::AnimationFlags, word_14) == 0x14);

// Zero-code semantic names for the two native 32-bit corner-anchor words.
#define TH20_HORIZONTAL_ANCHOR(flags) ((flags).word_10)
#define TH20_VERTICAL_ANCHOR(flags) ((flags).word_14)
