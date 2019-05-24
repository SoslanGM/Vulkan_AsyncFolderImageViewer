#version 450 core

// --- in ---
layout (location = 0) in vec2 uv;
layout (set = 0, binding = 1) uniform sampler2D tex;
// ---

// --- out ---
layout (location = 0) out vec4 color;
// ---


void main()
{
    color = texture(tex, uv);
}