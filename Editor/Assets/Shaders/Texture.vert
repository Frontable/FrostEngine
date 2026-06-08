






#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;


void main()
{
    TexCoords = texCoords;
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
}
