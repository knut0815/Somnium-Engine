#version 120

uniform vec2 light_position;

varying vec3 basicCol;

void main()
{
gl_FragColor = vec4(basicCol,1.0f);
}
