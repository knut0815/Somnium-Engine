#version 330 core

in vec2 vs_TexCoords;

uniform float threshold;
uniform sampler2D colourTexture;

void main()
{
	vec4 colour = texture(colourTexture, vs_TexCoords);
	float luma  = (colour.r * 0.2126) + (colour.g * 0.7152) + (colour.b * 0.0722);
	
	gl_FragColor = (colour * luma);
}
