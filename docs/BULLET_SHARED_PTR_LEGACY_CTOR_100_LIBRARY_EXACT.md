# CORE/EXACT-749 — original Bullet shared_ptr move construction, 46B + 54B complete STL source

**Two previously unmapped complete original TH20 executable functions now have real native-exact C++ STL implementations**, totaling 100 distinct original code bytes: the 46-byte shared_ptr<EtamaArgInf> move constructor and its 54-byte _Ptr_base<EtamaArgInf> move-construction helper. They are **library-origin**, not game-authored code. They do not add to game-authored strict byte credit. The 12,140B Bullet command Boss remains source-absent and NONEXACT.

Original locked target: Japanese TH20 v1.00a Steamless, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Actual original complete native functions and code provenance

| Whole original STL method | Original physical code head | Native size and x86 | New strict source unit |
| --- | --- | --- | --- |
| std::shared_ptr<EtamaArgInf> move constructor | 0x0047B820 | **46/46 bytes, 18 instructions** | shot_shared_ptr_move_ctor_library |
| std::_Ptr_base<EtamaArgInf>::_Move_construct_from | 0x0047ADA0 | **54/54 bytes, 19 instructions** | shot_ptr_base_move_construct_from_library |
| **Distinct original native STL physical intervals** | | **100 native bytes** | **2/2 new complete native strict units** |

The original 46B method has exactly three native E8 fields. Its 34 other native bytes are fully identical to the real pinned MSVC C++ template implementation. All three E8 positions and physical destinations come from the actual immutable original PE:

| Original E8 in 46B move constructor | Original target | Actual C++ method role |
| --- | --- | --- |
| 0x0047B82A | 0x00414030 | std::_Ptr_base<EtamaArgInf> default constructor, 33B folded-compatible physical original |
| 0x0047B833 | 0x0040B280 | std::move(shared_ptr<EtamaArgInf>&), 8B folded-compatible physical original |
| 0x0047B83F | 0x0047ADA0 | Separate real 54B _Ptr_base<EtamaArgInf>::_Move_construct_from |

The complete 54B child has **zero original native E8 or PE absolute relocation fields** and its entire 54/54 literal original bytes are exactly reproduced. It moves both genuine shared_ptr object/control-block pointer fields from its input into the destination and clears the two source fields. This is actual STL pointer ownership transfer, not a game-logic function.

The corresponding actual native MSVC 33B _Ptr_base default constructor is **byte-for-byte identical** to the already accepted physical 0x00414030 IntPoint default constructor code. The actual native 8B std::move operation is **byte-for-byte identical** to the previously accepted physical 0x0040B280 addressof-like forwarding alias. The two distinct C++ symbol/type identities are real, but their original physical code bytes **must not** be credited again. This evidence establishes fold-compatible aliases, not a proof of historical exact whole-program ICF flags.

## Independently verified original big-Boss and exact parent roles

The original whole **12,140B Bullet::run_extended_commands** at 0x0047DCF0 physically calls the 46B move constructor at its native **E8 0x0047F935 → 0x0047B820**, while constructing a real shared_ptr temporary in the Bullet command-copy workflow.

Separately, the already accepted complete **63B std::shared_ptr<EtamaArgInf> move assignment** at 0x0047C530 E8-calls the **same 46B original head** at **0x0047C549 → 0x0047B820**, before swapping and destroying the temporary. The 46B method itself E8-calls the 54B helper at **0x0047B83F → 0x0047ADA0**. These are three independent actual original PE direct-call operands, confirmed from whole original function bodies; none was inferred from a provisional Ghidra function name.

The initial Ghidra inventory incorrectly labeled the two 46B/54B heads as shared_ptr<_EXCEPTION_RECORD_const_> operations. That provisional type guess is disproved by the actual real EtamaArgInf shared pointer and the genuine MSVC C++ mangled symbols emitted by the source that reconstructs both entire original bodies.

## Real natural C++ source; no unrelated regression

The existing dedicated maintained source **src/ShotSharedPtrMoveLegacy.cpp** already reconstructed the original 63B std::shared_ptr<EtamaArgInf> move assignment, using the real old STL anonymous move-temporary, swap and destruction semantics. This checkpoint adds **one legitimate typed explicit MSVC C++20 template instantiation** of the genuine shared_ptr move constructor in the same existing owner. Its natural dependency emits the separate genuine 54B _Ptr_base move helper automatically.

The actual prior 63B original code remains byte-exact. No shared public header, game-owned ShotMetadata constructor code, custom STL override, fabricated wrapper, assembly, volatile, original PE byte, native relocation address or existing canonical mapping was altered.

Only that one affected source was rebuilt under its already pinned MSVC i386 compiler profile:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ShotSharedPtrMoveLegacy.cpp

**Result 3/3 strict original native whole functions, one cold object:** previous 63B move assignment 63/63, new 46B move ctor 46/46 and new 54B move helper 54/54. The original two noncanonical big parents remain separate game-code reconstruction tasks. A first private explicit instantiation without the constructor's required noexcept qualifier failed to compile and was corrected based on the actual pinned MSVC standard-library declaration, **without changing unrelated source**.

Reproducible evidence:
- .analysis/core747-ShotSharedPtrMoveCtor.cpp and its pinned actual native MSVC COFF object: private initial constructor probe with the real noexcept form.
- .analysis/core748-register-bullet-sharedptr-original-stl-move.py/json: original 46B/54B whole bodies, all three actual PE E8 targets, actual compiled 33B/8B aliases, existing 63B exact method preservation and new canonical strict unit definitions.
- Existing complete original 63B [shared_ptr move assignment source proof](SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md).
- New canonical units shot_shared_ptr_move_ctor_library and shot_ptr_base_move_construct_from_library in the same existing source provider.

**Accounting:** previously **1,201 canonical strict units /1,199 source-present functions**, now **1,203 units /1,201 source-present functions**, both new functions correctly marked library/exclude. Game-authored strict exact remains **556 complete functions /186,645 disjoint original code bytes**. The original 12,140B Bullet Boss remains NONEXACT, no full cold replay was run, and no historical shared_ptr COMDAT/ICF program-wide equivalence is asserted.
