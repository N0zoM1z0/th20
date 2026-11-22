# CORE/RECON-1245 — preserve the native trivial-node destroy_at call

The shared scalar allocator source now emits the original unconditional
std::destroy_at call for every non-null object, including types whose
destructors are trivial. This corrects a real source-to-native mismatch in
the 97-byte ECL intrusive-link release specialization at 0x00413B70.

## Original evidence and source correction

The original 97-byte release function contains an E8 at offset 0x20 to the
five-byte empty cdecl helper at 0x0040C6B0. That helper is the folded
std::destroy_at<IntrusiveLink<EclRuntime>> body. It is intentionally empty:
the link destructor is trivial, but the out-of-line destroy_at call is still
part of the original /Od allocator contribution.

The previous DiagnosticAllocator::release_object template used
if constexpr (!std::is_trivially_destructible_v<T>) around destroy_at. That
source-level shortcut removed the native empty helper call for
IntrusiveLink<EclRuntime>, leaving an 85-byte complete COFF contribution
instead of the original 97 bytes. The Runtime specialization remained
unaffected because EclRuntime has a nontrivial destructor.

The template now performs the natural unconditional operation:

1. Return immediately for a null pointer.
2. Call std::destroy_at(memory), even when that type's destructor is trivial.
3. Acquire recursive game-lock slot 1.
4. Release scalar storage with unsized operator delete.
5. Let the guard unlock and retain the native security-cookie epilogue.

No assembly, synthetic padding, destructor side effects or fake storage
operations are introduced. The trivial link's destroy_at body remains the
original empty five-byte helper and receives no duplicate physical credit.

## Focused verification

The affected-only strict source replays passed:

- EclRuntimeLifetime.cpp: 12/12, including both 97/97 release specializations
  and the 93/93 EclManager::terminate_async caller
- EnemyMesh.cpp: 7/7
- AnimationCallback.cpp: 9/9
- AnimationFilePreload269.cpp: 1/1
- AnimationPoolRelease308.cpp: 1/1
- ArchiveOwner.cpp: 8/8
- HitCtrlInfCreation.cpp: 4/4
- Bomb.cpp: 13/13
- GlyphTextureUpload360.cpp: 2/2
- LaserBase.cpp: 5/5
- DamageRegionLifetime.cpp: 1/1
- EclManagerTick.cpp: 1/1
- FunctionChainController.cpp: 15/15
- PlayerShotReset.cpp: 5/5
- GlyphCanvasAllocatorLifetime.cpp: 4/4
- BombCreation.cpp: 4/4
- Animation.cpp: 38/38

That is 130/130 configured units across 17 source-scoped cold objects.
The additional unregistered WeaponStoneProgressEffect.cpp,
WeaponStonePhaseEffect.cpp and WeaponStoneProgressMesh.cpp release callers
also compile under the locked i386 MSVC-compatible profile. The Enemy
dispatcher ASan/UBSan root verifier was rerun after the shared-header change:
all 29 i386 COFF units and the 800/801/802 root tests pass.

No whole-graph or full cold replay was run. The 41,967-byte Enemy dispatcher
remains NONEXACT.
