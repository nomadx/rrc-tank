#version 330

uniform mat3 u_normalMatrix;

in vec3 a_vertex;
in vec3 a_normal;

out vec3 g_normal;

void main(void)
{
	g_normal = u_normalMatrix * a_normal;
    
    gl_Position = vec4(a_vertex, 1);
}
