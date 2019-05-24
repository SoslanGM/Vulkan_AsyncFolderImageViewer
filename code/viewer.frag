#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

// --- in ---
layout (location = 0) in vec2 uv;
layout (location = 1) in flat int vi;
layout (set = 0, binding = 2) uniform sampler samp;
layout (set = 0, binding = 3) uniform texture2D tex[];
// ---

// --- out ---
layout (location = 0) out vec4 color;
// ---

void main()
{
    int index = vi / 4;
    color = texture(sampler2D(tex[index], samp), uv);
}