# Graphics rectangle submission — 1407B strict native reconstruction

The original 1407-byte Graphics rectangle routine at `0x00423650` is restored as natural C++ in `src/ScreenDrawRectangle1407.cpp`.

## Recovered behavior

1. Flushes the real `AnimationPoolOwner` submission queue before preparing the rectangle.
2. Uses the native 56B strided constructor helper at `0x0040BC20` and the real 43B `ColoredVertex` constructor at `0x00423470` to construct four contiguous 20-byte `XYZRHW | DIFFUSE` vertices.
3. Builds four positions from the input rectangle as `(left,top)`, `(right,top)`, `(left,bottom)`, `(right,bottom)`, using the original 54B `Vector3(float,float,float)` constructor for each position.
4. Applies the actual AnimationPoolOwner coordinate offsets at `+0xD0/+0xD4`, sets reciprocal W from the native `1.0f` constant at `0x0056C8CC`, and writes the supplied packed color to all four vertices.
5. Configures the original D3D9 texture-stage and render states, sets FVF `0x44`, and submits a two-primitive `D3DPT_TRIANGLESTRIP` using 20-byte vertices.
6. Resets the six real Renderer/AnimationPoolOwner cache hooks (`0x0041DB80`, `0x00424080`, `0x0041DBA0`, `0x0041DB60`, `0x0041DB40`, `0x004240A0`) and restores the four original texture-stage state values.

## Exactness evidence

The canonical `screen_draw_rectangle_1407` unit has passed whole-function C++20 replay at **1407/1407 bytes (1/1 exact)**. Its 56 relocation fields match the original 32 PE HIGHLOW targets and 24 direct E8 call targets. `scripts/verify-screen-draw-rectangle1407-native.py` independently pins the native SHA-256, all 24 physical call-site/target pairs, and all 32 physical HIGHLOW field/target pairs.

This is the shared Graphics rectangle submission callee used by all four ScreenInf solid/fade/hold/flash draw callbacks. The implementation uses existing Graphics, AnimationPoolOwner, ColoredVertex, Vector3 and D3D9 owners; no assembly, padding, synthetic vertex storage or replacement device state is used.
