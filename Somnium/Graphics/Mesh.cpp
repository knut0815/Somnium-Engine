#include "Mesh.h"

namespace Somnium
{
	namespace Graphics
	{
		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
			: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
		{
			setup();
		}

		Mesh::~Mesh()
		{
		}

		inline void Mesh::setup()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices, GL_DYNAMIC_DRAW); //Originally GL_STATIC_DRAW

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), &m_Indices, GL_DYNAMIC_DRAW); //Originally GL_STATIC_DRAW

			glEnableVertexAttribArray(SHADER_POSITION_INDEX);
			glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

			glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);
			glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

			glBindVertexArray(0);
		}

		void Mesh::draw(Shader& shader)
		{
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0); //TODO: Binding/unbinding every object is a waste of processing!!! OPTIMISE!
		}
	}
}
