#pragma once

#include <glew.h>
#include "../Maths/Maths.h"
#include "Shader.h"
#include <vector>
#include <string>

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
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Shader& shader );
			~Mesh();

			inline void bind() const { glBindVertexArray(m_VAO); }
			inline void unbind() const { glBindVertexArray(0); }

			inline bool structureExists() const { return !m_Vertices.empty() && !m_Indices.empty(); }
			const inline GLuint getVAO() const { return m_VAO; }
			const inline size_t getIBOSize() const { return m_Indices.size(); }
			inline Shader& getShader() const { return m_Shader; }
			Maths::Matrix4 getModelMatrix();

			void setPosition(float x, float y, float z) { setPosition(Maths::Vector3(x, y, z)); }
			void setPosition(Maths::Vector3 position) { m_Position = position; }

			void rotate(float xAngleOffset, float yAngleOffset, float zAngleOffset) { rotate(Maths::Vector3(xAngleOffset, yAngleOffset, zAngleOffset)); }
			void rotate(Maths::Vector3 rotationOffset) { m_Orientation += rotationOffset; };

			void translate(float xOffset, float yOffset, float zOffset) { translate(Maths::Vector3(xOffset, yOffset, zOffset)); }
			void translate(Maths::Vector3 offset) { m_Position += offset; };

		private:
			inline void init();

		private:
			GLuint m_VAO, m_VBO, m_IBO;

			Shader& m_Shader;

			const std::vector<Vertex> m_Vertices;
			const std::vector<GLuint> m_Indices;
			const std::vector<Texture> m_Textures;

			Maths::Vector3 m_Position = Maths::Vector3(0, 0, 0);
			Maths::Vector3 m_Scale = Maths::Vector3(1, 1, 1);
			Maths::Vector3 m_Orientation = Maths::Vector3(0, 0, 0);
		};
	}
}
