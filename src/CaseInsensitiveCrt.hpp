#pragma once
#include <cstring>
// The Windows CRT retains its full locale/failure behavior. Portable tests
// fixture the valid ASCII domain, without replacing the native API by strcmp.
#if !defined(_WIN32)
extern "C" int _stricmp(const char*, const char*);
#endif
