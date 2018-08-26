#version 330 core

uniform	mat4 projectionMatrix;
uniform mat4 viewMatrix;

layout (location = 0) in vec3 position;

out vec3 basicCol;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0f);
	
	if(position.x != 0.0  && position.z != 0.0)
		basicCol = vec3(0.75,0.75,0.75);
	else
		basicCol = vec3(position.x != 0.0, position.y != 0.0, position.z != 0.0);
}
