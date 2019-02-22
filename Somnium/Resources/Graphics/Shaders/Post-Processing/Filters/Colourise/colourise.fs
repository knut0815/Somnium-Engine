 #version 330 core

in vec2 vs_TexCoords;

out vec4 FragColour;

uniform sampler2D colourTexture;
uniform vec3 colourise;

void main()
{
	vec4 colour = texture(colourTexture, vs_TexCoords);
	
	vec4 colour = texture(colourTexture, vs_TexCoords);
	float newColour = dot(colour.rgb, colourise);
	
	FragColour = vec4(vec3(newColour), 1.0f);
}
