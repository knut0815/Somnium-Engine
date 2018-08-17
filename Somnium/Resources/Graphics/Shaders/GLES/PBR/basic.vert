#version 100
attribute vec3 position;
attribute vec3 normals;
attribute vec2 texCoords;

varying vec2 TexCoords;
varying vec3 WorldPos;
varying vec3 Normal;
varying vec3 VertPos;

uniform	mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = texCoords;
    WorldPos = vec3(modelMatrix * vec4(position, 1.0));
    Normal = mat3(modelMatrix) * normals;   
    VertPos = position;
	
    gl_Position =  projectionMatrix * viewMatrix * vec4(WorldPos, 1.0);
}

