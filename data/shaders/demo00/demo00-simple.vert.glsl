#version 150 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 in_Position;
in vec3 in_Color;

out vec3 pass_Color;

void main(void)
{
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
     pass_Color = in_Color;
}