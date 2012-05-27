#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 inPosition;
in vec2 inTexCoord;

out vec2 texCoord;

void main(void)
{
    texCoord = inTexCoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1.0);
}
