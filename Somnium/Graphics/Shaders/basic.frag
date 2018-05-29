#version 330 core

uniform vec4 colour;
uniform vec2 light_position;

void main()
{
	gl_FragColor = colour;
}
