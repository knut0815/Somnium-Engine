#version 100

uniform	mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

attribute vec3 position;
attribute vec3 normals;
//attribute vec2 texCoords;

//varying vec2 textureCoords;
varying vec3 worldPos;
varying vec3 normal;
varying vec3 vertPos;

void main()
{
  //  textureCoords = texCoords;
    worldPos = vec3(modelMatrix * vec4(position, 1.0));
    normal = mat3(modelMatrix) * normals;   
    vertPos = position;
	
    gl_Position =  projectionMatrix * viewMatrix * vec4(worldPos, 1.0);
}

