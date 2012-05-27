#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec3 inPosition;
in vec3 inNormal;

out vec3 vEye;
out vec3 vNormal;


void main(void)
{
    vec4 vertex = viewMatrix * modelMatrix * vec4(inPosition, 1.0);
    vEye        = -vec3(vertex);
    vNormal     = normalMatrix * inNormal;    
    gl_Position = projectionMatrix * vertex;;
}
