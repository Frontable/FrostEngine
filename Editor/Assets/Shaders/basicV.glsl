#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUV;

uniform mat4 uProjection;

out vec2 UV;

void main()
{
    UV = vUV;
    gl_Position = uProjection * vec4(vPos.x, vPos.y, vPos.z, 1.0);
}