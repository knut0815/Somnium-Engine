#version 330 core

in vec2 texCoords;

uniform sampler2D texFramebuffer;

void main()
{
	gl_FragColor = texture(texFramebuffer, texCoords);
}
