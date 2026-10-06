// Infrastructure probe; this is not reconstructed TH20 source or a match unit.
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include <xinput.h>
#include <gdiplus.h>
#include <cstdio>

extern "C" __declspec(noinline) unsigned th20_probe_mix(unsigned value)
{
    return (value * 1664525u) + 1013904223u;
}

int main()
{
    static_assert(sizeof(void *) == 4, "TH20 exact ABI requires x86 pointers");
    static_assert(_MSC_FULL_VER == 194435211, "unexpected MSVC compiler");
    D3DXVECTOR3 vector(1.0f, 2.0f, 3.0f);
    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix); // Forces real legacy D3DX header + import-library linkage.
    unsigned result = th20_probe_mix(123u);
    std::printf("TH20 toolchain smoke: MSVC=%d pointers=%u result=%u tick=%lu\n",
                _MSC_FULL_VER, unsigned(sizeof(void *)), result, GetTickCount());
    return result == 1218640798u && vector.z == 3.0f && matrix._11 == 1.0f ? 0 : 1;
}
