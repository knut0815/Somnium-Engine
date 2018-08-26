#version 100

uniform	mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

attribute vec3 position;
attribute vec3 normals;
attribute vec2 texCoords;

varying vec3 basicCol;
varying vec3 worldPos;

void main()
{
	worldPos = vec3(modelMatrix * vec4(position, 1.0));
	gl_Position = projectionMatrix * viewMatrix * vec4(worldPos, 1.0);
	basicCol = position;
}
