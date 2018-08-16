#version 100

uniform	mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

attribute vec3 position;
attribute vec3 normals;
attribute vec3 texCoords;

varying vec3 basicCol;

void main()
{
	gl_Position = projectionMatrix * viewMatrix* modelMatrix * vec4(position, 1.0);
	basicCol = position;
}
