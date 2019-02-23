 #version 330 core

in vec2 vs_TexCoords;

out vec4 FragColour;

uniform vec3 colourise;
uniform float strength;
uniform sampler2D colourTexture;

void main()
{
	vec4 colour = texture(colourTexture, vs_TexCoords);
	float grey = dot(colour.rgb, vec3 (0.299, 0.587, 0.114));
	vec4 newColour = vec4(grey * colourise, colour.a);
	
	FragColour = mix(colour, newColour, strength) * colour.a;
}
