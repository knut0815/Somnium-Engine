 #version 330 core

in vec2 vs_TexCoords;

uniform sampler2D original;
uniform sampler2D blurred;
uniform float exposure;

void main()
{
	const float gamma = 2.2;
	vec3 hdrColour = texture(original, vs_TexCoords).rgb;
	vec3 bloomColour = texture(blurred, vs_TexCoords).rgb;

	hdrColour += bloomColour;
	vec3 result = vec3(1.0) - exp(-hdrColour * exposure);

	result = pow(result, vec3(1.0 / gamma));
	gl_FragColor = vec4(result, 1.0);
}
