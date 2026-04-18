#version 330 core
in vec2 UV;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    //FragColor = vec4(0.3, 0.5, 0.6, 1.0);
    FragColor = texture(tex, UV);
}