#version 330 core

in vec2 vs_TexCoords;

out vec4 FragColour;

uniform float threshold;
uniform sampler2D colourTexture;

void main()
{
	vec4 colour = texture(colourTexture, vs_TexCoords);
	float grey = dot(colour.rgb, vec3 (0.299, 0.587, 0.114));
	
	FragColour = vec4(vec3(grey), 1.0f);
}
