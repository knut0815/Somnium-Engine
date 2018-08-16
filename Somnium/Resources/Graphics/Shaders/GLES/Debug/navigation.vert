#version 100

uniform	mat4 projectionMatrix;
uniform mat4 viewMatrix;

attribute vec3 position;

varying vec3 basicCol;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
	if(position.x != 0.0 && position.y == 0.0 && position.z == 0.0)
	{
		basicCol = vec3(1,0,0);
	}
	else if(position.x == 0.0 && position.y != 0.0 && position.z == 0.0)
	{
		basicCol = vec3(0,1,0);
	}
	else if(position.x == 0.0 && position.y == 0.0 && position.z != 0.0)
	{
		basicCol = vec3(0,0,1);
	}
	else
	{
		basicCol = vec3(0.75,0.75,0.75);
	}
}
