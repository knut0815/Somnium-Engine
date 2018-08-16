#version 330 core

uniform vec2 light_position;

in vec3 basicCol;

out vec4 FragColor;

void main()
{
FragColor = vec4(basicCol,1.0f);
}
