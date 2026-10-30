// CORE/RECON-981: complete original 188B Direct3D9 texture surface clear.
// Original source uses real COM API and original no-op null branch.
#include <d3d9.h>
#include <cstring>
namespace th20 {
void __fastcall clear_texture_surface_449d80(IDirect3DTexture9** texture_slot) {
    IDirect3DSurface9* surface;
    (*texture_slot)->GetSurfaceLevel(0, &surface);
    if(surface == nullptr) { } else {
        D3DSURFACE_DESC desc;
        D3DLOCKED_RECT rect;
        surface->GetDesc(&desc);
        surface->LockRect(&rect, nullptr, 0);
        std::memset(rect.pBits,0,rect.Pitch*desc.Height);
        surface->UnlockRect();
        if (surface) { surface->Release(); surface=nullptr; }
    }
}
}
