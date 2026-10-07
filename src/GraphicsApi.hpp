#pragma once
#include <cstdint>
#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <d3d9.h>
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#endif
namespace th20::graphics_api {
#if defined(_WIN32)
using Direct3D = IDirect3D9;
using Device = IDirect3DDevice9;
using Resource = IUnknown;
using WindowHandle = HWND;
using WindowRect = RECT;
using InputDeviceCaps = DIDEVCAPS;
using Presentation = D3DPRESENT_PARAMETERS;
using DisplayMode = D3DDISPLAYMODE;
using DeviceCaps = D3DCAPS9;
#else
struct Direct3D;
struct Device;
struct Resource;
using WindowHandle = void*;
// Portable API records for owned tests. Native builds use actual SDK types.
struct WindowRect { std::int32_t left, top, right, bottom; };
struct InputDeviceCaps {
    std::uint32_t dwSize, dwFlags, dwDevType, dwAxes, dwButtons, dwPOVs;
    std::uint32_t dwFFSamplePeriod, dwFFMinTimeResolution;
    std::uint32_t dwFirmwareRevision, dwHardwareRevision, dwFFDriverVersion;
};
struct Presentation {
    std::uint32_t BackBufferWidth, BackBufferHeight, BackBufferFormat, BackBufferCount;
    std::uint32_t MultiSampleType, MultiSampleQuality, SwapEffect;
    void* hDeviceWindow;
    std::int32_t Windowed, EnableAutoDepthStencil;
    std::uint32_t AutoDepthStencilFormat, Flags;
    std::uint32_t FullScreen_RefreshRateInHz, PresentationInterval;
};
struct DisplayMode { std::uint32_t Width, Height, RefreshRate, Format; };
struct D3DVSHADERCAPS2_0 {
    std::uint32_t Caps;
    std::int32_t DynamicFlowControlDepth;
    std::int32_t NumTemps;
    std::int32_t StaticFlowControlDepth;
};
struct D3DPSHADERCAPS2_0 {
    std::uint32_t Caps;
    std::int32_t DynamicFlowControlDepth;
    std::int32_t NumTemps;
    std::int32_t StaticFlowControlDepth;
    std::int32_t NumInstructionSlots;
};
struct D3DCAPS9 {
    std::uint32_t  DeviceType;
    std::uint32_t        AdapterOrdinal;
    std::uint32_t   Caps;
    std::uint32_t   Caps2;
    std::uint32_t   Caps3;
    std::uint32_t   PresentationIntervals;
    std::uint32_t   CursorCaps;
    std::uint32_t   DevCaps;
    std::uint32_t   PrimitiveMiscCaps;
    std::uint32_t   RasterCaps;
    std::uint32_t   ZCmpCaps;
    std::uint32_t   SrcBlendCaps;
    std::uint32_t   DestBlendCaps;
    std::uint32_t   AlphaCmpCaps;
    std::uint32_t   ShadeCaps;
    std::uint32_t   TextureCaps;
    std::uint32_t   TextureFilterCaps;
    std::uint32_t   CubeTextureFilterCaps;
    std::uint32_t   VolumeTextureFilterCaps;
    std::uint32_t   TextureAddressCaps;
    std::uint32_t   VolumeTextureAddressCaps;
    std::uint32_t   LineCaps;
    std::uint32_t   MaxTextureWidth, MaxTextureHeight;
    std::uint32_t   MaxVolumeExtent;
    std::uint32_t   MaxTextureRepeat;
    std::uint32_t   MaxTextureAspectRatio;
    std::uint32_t   MaxAnisotropy;
    float   MaxVertexW;
    float   GuardBandLeft;
    float   GuardBandTop;
    float   GuardBandRight;
    float   GuardBandBottom;
    float   ExtentsAdjust;
    std::uint32_t   StencilCaps;
    std::uint32_t   FVFCaps;
    std::uint32_t   TextureOpCaps;
    std::uint32_t   MaxTextureBlendStages;
    std::uint32_t   MaxSimultaneousTextures;
    std::uint32_t   VertexProcessingCaps;
    std::uint32_t   MaxActiveLights;
    std::uint32_t   MaxUserClipPlanes;
    std::uint32_t   MaxVertexBlendMatrices;
    std::uint32_t   MaxVertexBlendMatrixIndex;
    float   MaxPointSize;
    std::uint32_t   MaxPrimitiveCount;
    std::uint32_t   MaxVertexIndex;
    std::uint32_t   MaxStreams;
    std::uint32_t   MaxStreamStride;
    std::uint32_t   VertexShaderVersion;
    std::uint32_t   MaxVertexShaderConst;
    std::uint32_t   PixelShaderVersion;
    float   PixelShader1xMaxValue;
    std::uint32_t   DevCaps2;
    float   MaxNpatchTessellationLevel;
    std::uint32_t   Reserved5;
    std::uint32_t    MasterAdapterOrdinal;
    std::uint32_t    AdapterOrdinalInGroup;
    std::uint32_t    NumberOfAdaptersInGroup;
    std::uint32_t   DeclTypes;
    std::uint32_t   NumSimultaneousRTs;
    std::uint32_t   StretchRectFilterCaps;
    D3DVSHADERCAPS2_0 VS20Caps;
    D3DPSHADERCAPS2_0 PS20Caps;
    std::uint32_t   VertexTextureFilterCaps;
    std::uint32_t   MaxVShaderInstructionsExecuted;
    std::uint32_t   MaxPShaderInstructionsExecuted;
    std::uint32_t   MaxVertexShader30InstructionSlots;
    std::uint32_t   MaxPixelShader30InstructionSlots;
};
using DeviceCaps = D3DCAPS9;
#endif
static_assert(sizeof(InputDeviceCaps) == 44);
static_assert(sizeof(DeviceCaps) == 304);
#if defined(_M_IX86)
static_assert(sizeof(Presentation) == 56);
#endif
}
