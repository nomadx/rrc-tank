#version 150

in vec3 inPosition;
in vec3 inColour;

out vec3 vertColour;

void main()
{
    gl_Position = vec4(inPosition, 1.0);
    vertColour = inColour;
}
