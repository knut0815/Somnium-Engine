#pragma once

#include <glew.h>
#include "../Maths/Maths.h"
#include "Shader.h"
#include <vector>

#define NUM_BUFFERS
#define SHADER_POSITION_INDEX 0
#define SHADER_NORMAL_INDEX 1
#define SHADER_TEXTURE_COORDINATE_INDEX 2

namespace Somnium
{
	namespace Graphics
	{
		struct Vertex
		{
			Maths::Vector3 position;
			Maths::Vector3 normal;
			Maths::Vector2 texCoords;
		};

		struct Texture
		{
			GLuint id;
			std::string type;
		};

		class Mesh
		{
		public:
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
			~Mesh();

			void Draw(Shader& shader);

			inline GLuint GetVAO() const { return m_VAO; }

		private:
			inline void Setup();

		private:
			GLuint m_VAO, m_VBO, m_EBO;

			const std::vector<Vertex> m_Vertices;
			const std::vector<GLuint> m_Indices;
			const std::vector<Texture> m_Textures;
		};
	}
}