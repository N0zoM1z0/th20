// Locked-MSVC compatibility source for the original 63-byte STL
// std::shared_ptr<EtamaArgInf> move-assignment body (0x0047C530).
// This is reconstructed LIBRARY support, not hand-authored game logic.
// The source rebuilds the genuine anonymous temporary / swap / destructor
// lifetime and the genuine old non-inlined std::move forwarding operation.
// No asm, manual relocation patch, NOP shaping, raw pointer type punning,
// or changes to the shared EtamaArgInf value layout are used.
// This local translation unit reconstructs the old STL *source behavior*;
// original whole-program template/COMDAT selection remains unproved.
#include "ShotMetadata.hpp"
#include <memory>
#include <utility>

namespace std {
template <>
__declspec(noinline)
shared_ptr<EtamaArgInf>&& move<shared_ptr<EtamaArgInf>&>(shared_ptr<EtamaArgInf>& other) noexcept {
    return static_cast<shared_ptr<EtamaArgInf>&&>(other);
}

template <>
shared_ptr<EtamaArgInf>&
shared_ptr<EtamaArgInf>::operator=(shared_ptr<EtamaArgInf>&& other) noexcept {
    // Historic actual STL idiom: anonymous move temporary calls swap,
    // whereas a named local changes original /Od EAX/stack lifetime.
    shared_ptr<EtamaArgInf>(std::move(other)).swap(*this);
    return *this;
}
}
