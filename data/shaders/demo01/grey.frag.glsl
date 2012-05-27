#version 330

uniform sampler2D uTexture; 

in vec2 texCoord;

layout(location = 0, index = 0) out vec4 fragColor;

void main(void)
{
    vec4 color = texture(uTexture, texCoord);
	fragColor = color;
    
    if (texCoord.s >= 0.5)
    {
        float grey = color.r*0.299 + color.g*0.587 + color.b*0.114;        
        fragColor = vec4(grey, grey, grey, 1.0f);
    }
    else
    {
        fragColor = color;
    }
}
