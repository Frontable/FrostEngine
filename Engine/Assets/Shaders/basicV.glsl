#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vUV;

uniform mat4 uProjection;

out vec2 UV;

void main()
{
    UV = vUV;
    gl_Position = uProjection * vec4(vPos, 0.0, 1.0);
}