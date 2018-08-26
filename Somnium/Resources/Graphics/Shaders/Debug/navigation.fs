#version 330 core

in vec3 basicCol;

out vec4 FragColour;

void main()
{
	FragColour = vec4(basicCol,1.0f);
}
