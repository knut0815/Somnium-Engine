#version 330 core

uniform vec2 light_position;

in vec3 basicCol;

void main()
{
gl_FragColor = vec4(basicCol,1.0f);
}
