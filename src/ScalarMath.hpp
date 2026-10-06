#pragma once

namespace th20::scalar_math {

// Native cdecl wrappers widen arguments to the double CRT and narrow the result.
float sine(float value);
float cosine(float value);
float square_root(float value);
float arctangent(float y, float x);

} // namespace th20::scalar_math
