# CORE/RECON-777 — original 43-byte SprtID predicate, by-value lambda capture and folded physical code

Original immutable Japanese TH20 v1.00a Steamless PE SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint recovers the genuine source-level ID capture category in the
entire previously accepted 456B Animation handle resolver and admits
**one new distinct whole game-authored original 43-byte /15-x86 body at
`0x00449600`**. Both original lambda types generate identical whole native
operator code but point to **one physical original function**; no duplicate
original body or invented game byte count is recorded.

## Correct the older by-reference hypothesis using original PE, not docs

The earlier CORE/RECON-757/772 discussion labeled two original
`SprtCtrlInf::getSprt(SprtID)` lambdas as reference-capturing. That was an
unverified inference based on the address passed to their constructors,
not the captured data's actual lifetime. Re-reading the immutable original
PE shows that the **26B constructor at `0x00447960` dereferences its input
pointer and copies the *four-byte ID value* into the lambda closure**:
`mov ecx, [eax]` at `0x0044796A`, then `mov [edx], ecx` at `0x0044796F`.
This is evidence for capture **by value**, not for storing an external
pointer by reference. The callback itself at `0x00449600` loads its lambda
receiver, directly pushes the receiver's pointer as a `SprtID` reference
and calls the genuine `SprtID::operator==(const SprtID&)` at `0x00449400`.
A reference capture instead dereferences the stored pointer and produces
an extra pointer/stack temporary in the compiled lambda.

The original executable's two distinct `std::function` callable vtables,
with original PE HIGHLOW pointers at `0x0056E600..0x0056E614` and
`0x0056E61C..0x0056E630`, **both refer at their third entry** to the
same physical `_Do_call` at `0x0044B3D0`. It forwards through the actual
`0x00447920` invoker to **the same** 43B `0x00449600` body. The two
original RTTI lambda identities remain distinct and must not be collapsed
into a single original capture constructor or `std::function` owner;
only their actual folded predicate body receives one physical credit.

## Entire original 43-byte body and source reconstruction

The original complete 15-instruction body has exactly two real E8 calls:

| Immutable original call site | Original E8 destination | Real role |
| --- | --- | --- |
| `0x0044960C` | `0x0040C300` | `IntrusiveLink<Animation>::node_value()` returns linked `Animation*` |
| `0x00449620` | `0x00449400` | original separately strict 47B `SprtID` reference equality, on `Animation+0x4C0` |

There are **zero HIGHLOW data relocations** in this body. The 43-byte
function ends in the original `ret 4`; every original byte and original
E8 field is included in the comparison. The maintained C++ lambdas in the
single shared `src/AnimationPoolHandleResolve.cpp` use natural **four-byte
by-value** capture `[raw_id]`, with a typed `SprtID` lvalue view of that
capture and of the linked Animation's four-byte ID. This respects the
already accepted public `uint32_t`/four-byte caller ABI; no public header
retyping, invented adapters or assembly are involved.

Under pinned MSVC 19.44.35211 x86, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, **both generated lambda `operator()` bodies
replay 43/43 whole native bytes and 15/15 instruction heads** with the
same two independently original E8 target roles. The canonical unit
`animation_pool_sprt_equal_lambda_43` uses the first lambda's genuine
MSVC-defined COFF symbol and **credits only one** physical original
function at `0x00449600`. The second callable is a compatible compiled
alias, not a separately mapped 43-byte game function.

The original 26B lambda capture constructor itself remains a **separate
noncredited compiler-generated function**: the modern by-value compiler
constructor still has differing individual bytes from original
`0x00447960`. Matching the new predicate does **not** imply that the
constructor or the whole game link has been independently accepted.

## Changed-only validation and game code accounting

The source correction from `[&raw_id]` to `[raw_id]` changes only the already
canonical `src/AnimationPoolHandleResolve.cpp` provider and two private
compiler lambda-constructor symbols inside its **previously entire exact
456-byte resolver**. The independently native original E8 destinations of
both constructor sites (`0x0044CD80` and `0x0044CDDD`, each original
`0x00447960`) remain unchanged; the two symbol names in the canonical
manifest were reconciled after confirming complete original code identity
and the physical E8 destination. The original 456B parent code retains
**141/141 x86 and 20/20 original E8 source fields**.

The single affected source object was cold compiled and completely replayed
under the locked compiler; **all 4/4 strict whole-native methods** are now
exact from its one physical object and receipt: the original **456B
resolver, 159B link walker, 154B list wrapper and new 43B predicate**.
Only this affected source was rebuilt, no shared header changed and no
unfiltered whole-graph cold replay was run:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPoolHandleResolve.cpp
    scripts/repo-python scripts/verify-animation-pool-resolver-native.py

Original game authored exact coverage progresses from **568/187,955B** to
**569/187,998B**, one whole physical game method and 43 bytes. Source-present
mappings go **1,213 →1,214**, strict canonical units **1,215 →1,216**, and
the number of protected distinct canonical object/receipt providers remains
**249**. The 12,140B Bullet command parent, 41,967B Enemy ECL dispatcher
and 39,470B Animation VM remain NONEXACT. Exact predicate code does not
establish whole-executable linkage or a playable game.
