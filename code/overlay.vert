#version 450 core

// --- in ---
layout (location = 0) in vec4 coord;
layout (location = 1) in vec2 uv;
layout (set = 0, binding = 0) uniform matrix
{
    mat4 orthographic;
};
// ---

// --- out ---
layout (location = 0) out vec2 _uv;
// ---


void main()
{
    gl_Position = coord * orthographic;
    _uv = uv;
}