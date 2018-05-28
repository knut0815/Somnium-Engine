#version 330 core

layout (location = 0) in vec3 position;

out vec4 vertexColour;

void main()
{
	gl_Position = vec4(position, 1);
	vertexColour = vec4(1,1,1,1);
}