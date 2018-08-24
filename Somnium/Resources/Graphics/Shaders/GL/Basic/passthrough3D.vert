 #version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;

out vec3 vs_Position;
out vec3 vs_Normals;
out vec2 vs_TexCoords;

void main()
{
	gl_Position = vec4(position, 1.0);
	vs_Position = position;
	vs_Normals = normals;
	vs_TexCoords = texCoords;
}
