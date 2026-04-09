#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vUV;
layout (location = 2) in vec4 vColor;

out vec2 UV;
out vec4 FragColor;

uniform mat4 proj;

void main()
{
    FragColor = vColor;
    UV = vUV;
    gl_Position = proj * vec4(vPos, 0.0, 1.0);
}