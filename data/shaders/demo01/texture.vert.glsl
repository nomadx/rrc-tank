#version 150

uniform mat4 uMVP;

in vec4 inPosition;
in vec2 inTexCoord;

out vec2 texCoord;

void main(void)
{
    texCoord = inTexCoord;

    gl_Position = uMVP * inPosition;
}
