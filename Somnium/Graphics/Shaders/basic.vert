#version 330 core

uniform Matrices{
	mat4 projectionMatrix;
	mat4 modelMatrix;
};

layout (location = 0) in vec3 position;


void main()
{
	gl_Position = projectionMatrix * modelMatrix * vec4(position, 1);
}
