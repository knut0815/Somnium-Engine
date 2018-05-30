#version 120

uniform	mat4 projectionMatrix;
uniform mat4 modelMatrix;

attribute vec3 position;
attribute vec3 normals;
attribute vec3 texCoords;

varying vec3 basicCol;

void main()
{
	gl_Position = projectionMatrix * modelMatrix * vec4(position, 1.0f);
	basicCol = position;
}
