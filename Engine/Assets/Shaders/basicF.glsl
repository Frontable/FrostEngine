#version 330 core
out vec4 FragColor;
in vec2 UV;


uniform sampler2D tex;
uniform bool useTexture;

void main()
{
    if(useTexture)
    {
        FragColor = texture(tex, UV);
    } else 
    {
        FragColor = vec4(1.0, 0.8, 0.4, 1.0);
    }
}