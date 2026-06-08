#version 330 core
in vec2 UV;
in vec4 FragColor;
out vec4 FinalColor;

uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, UV);
    FinalColor = mix(texColor, FinalColor, 0.1);
}
