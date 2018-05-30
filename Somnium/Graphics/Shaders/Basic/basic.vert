#version 330 core

uniform	mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 rMatrix;
uniform mat4 sMatrix;
uniform mat4 tMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec3 texCoords;

out vec3 basicCol;

void main()
{
	gl_Position = projectionMatrix * tMatrix * rMatrix * sMatrix * vec4(position, 1.0f);
	basicCol = position;
}
