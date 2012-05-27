#version 330

in vec3 inPosition;
in vec3 inColour;

uniform mat4 uMVP;

out vec3 vertColour;

void main()
{
    gl_Position = uMVP * vec4(inPosition, 1.0);
    vertColour = inColour;    
}
