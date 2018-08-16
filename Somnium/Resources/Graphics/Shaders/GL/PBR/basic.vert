#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoords;


out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;
out vec3 VertPos;

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

