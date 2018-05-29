#version 330 core

uniform vec4 colour;
uniform vec2 light_position;

out vec4 FragColor;

void main()
{
	FragColor = colour;
}
