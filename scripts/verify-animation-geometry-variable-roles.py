#!/usr/bin/env python3
"""Verify mode-specific ANM variable aliases used by exact Animation geometry."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
variables = (ROOT / "src/AnmVariables.hpp").read_text()
geometry = (ROOT / "src/AnimationGeometry.cpp").read_text()

aliases = {
    "geometry_uv_v_span": 4,
    "rounded_shape_radius": 16,
    "ring_center_radius": 16,
    "mode24_25_angular_span": 16,
    "mode47_ring_thickness": 16,
    "mode48_triangle_radius": 16,
    "ring_thickness": 20,
    "mode24_25_half_height": 20,
    "mode47_ring_center_radius": 20,
    "mode24_25_base_radius": 24,
    "mode24_25_center_angle": 28,
}
integer_aliases = {"geometry_uv_v_span"}
for name, offset in aliases.items():
    declared_type = "std::int32_t" if name in integer_aliases else "float"
    assert f"{declared_type} {name};" in variables, name
    assert f"offsetof(AnmVariables, {name}) == {offset}" in variables, name

assert "base.variables.mode47_ring_thickness" in geometry
assert "base.variables.mode47_ring_center_radius" in geometry
assert "base.variables.mode48_triangle_radius" in geometry
assert "base.variables.mode24_25_angular_span" in geometry
assert "base.variables.mode24_25_half_height" in geometry
assert "base.variables.geometry_uv_v_span" in geometry
assert "base.variables.mode24_25_base_radius" in geometry
assert "base.variables.mode24_25_center_angle" in geometry
assert "base.variables.field_10" not in geometry
assert "base.variables.field_14" not in geometry
assert "base.variables.field_04" not in geometry
assert "base.variables.field_18" not in geometry
assert "base.variables.field_1c" not in geometry
assert "sizeof(AnmVariables) == 64" in variables

print("PASS mode-specific ANM variable roles: modes24/25, 37/38, 39-41, 47 and 48")
print("PASS all aliases retain original offsets and 64B storage")
print("PASS exact Animation::update_geometry source has no anonymous +0x10/+0x14 reads")
