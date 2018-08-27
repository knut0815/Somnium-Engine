#version 330 core

in vec2 vs_TexCoords;

out vec4 FragColour;

uniform sampler2D colourTexture;

void main()
{
	vec4 colour = texture(colourTexture, vs_TexCoords);
	
	float red = min(dot(colour, vec4(0.393f, 0.769f, 0.189f, 0)), 255);
	float green = min(dot(colour, vec4(0.349f, 0.686f, 0.168f, 0)), 255);
	float blue = min(dot(colour, vec4(0.272f, 0.534f, 0.131f, 0)), 255);

	FragColour = vec4(red, green, blue, 1.0f);
}
