# Indexed Animation SpriteData accessor — 0x00437CA0

The previously unclassified 38-byte function at 0x00437CA0 is the indexed
Animation::sprite_data(std::int32_t) accessor. Its caller at 0x00438F10
loads the selector from Animation+0x20, pushes it, and calls this wrapper.
The wrapper then delegates through the existing, independently exact accessors:

1. Animation::animation_file() at 0x00437500
2. AnimationFile::sprite(index) at 0x00437C80

The recovered source is ordinary C++:

    SpriteData* Animation::sprite_data(std::int32_t index) {
        AnimationFile* file = animation_file();
        return file->sprite(index);
    }

The pinned MSVC /Od /Ob0 object reproduces the full original 38-byte function.
Strict canonical comparison confirms all 30 non-relocation bytes and both
original REL32 fields at offsets 0x0D and 0x1C, resolving to 0x00437500
and 0x00437C80. The corresponding AnimationSpriteAccess.cpp object was
rebuilt and all four accessors in that translation unit verify strictly:

- Animation::animation_file: 29/29
- AnimationFile::sprite: 23/23
- Animation::sprite_data(): 45/45
- Animation::sprite_data(index): 38/38

This is a real indexed accessor, not a duplicate of the no-argument
Animation::sprite_data() method. It uses the existing AnimationFile and
SpriteData types and adds no object storage or assembly.
