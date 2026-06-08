#version 330 core
out vec4 FragColor;
in vec2 UV;


uniform sampler2D tex;
uniform bool useTexture;

void main()
{
    vec4 texColor = texture(tex, UV);
    
    if(useTexture)
    {   
        if(texColor.a < 0.1) 
        {
            discard; // Prevents transparent pixels from writing to depth buffer
        }
        FragColor = texture(tex, UV);
    } else 
    {
        FragColor = vec4(1.0, 0.8, 0.4, 1.0);
    }
}