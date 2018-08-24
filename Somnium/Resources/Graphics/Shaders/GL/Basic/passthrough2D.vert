 #version 330 core

layout(location = 0) in vec2 position;
layout(location = 2) in vec2 texCoords;

out vec2 vs_Position;
out vec2 vs_TexCoords;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	vs_Position = position;
	vs_TexCoords = texCoords;
}
