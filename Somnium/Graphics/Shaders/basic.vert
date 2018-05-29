#version 330 core

uniform mat4 pr_matrix;
uniform mat4 ml_matrix;
uniform vec4 scale;

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = pr_matrix * ml_matrix * vec4(position, 1);
}
