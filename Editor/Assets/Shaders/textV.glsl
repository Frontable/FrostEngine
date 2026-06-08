#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 TexCoords;

uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * vec4(aPos, 1.0);
    TexCoords = aUV;
}