#version 450 core

// --- in ---
layout (location = 0) in vec4 coord;
layout (location = 1) in vec2 uv;
layout (set = 0, binding = 0) uniform a
{
    mat4 ortho;
};
layout (set = 0, binding = 1) uniform b
{
    mat4 view;
};
// ---

// --- out ---
layout (location = 0) out vec2 _uv;
layout (location = 1) out int _vi;
// ---

void main()
{
    gl_Position = coord * view * ortho;
    _uv = uv;
    _vi = gl_VertexIndex;
}