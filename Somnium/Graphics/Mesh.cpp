#include "Mesh.h"

namespace Somnium
{
	namespace Graphics
	{
		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
			: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
		{
			init();
		}

		Mesh::~Mesh()
		{
			glDeleteVertexArrays(1, &m_VAO);
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_IBO);
		}

		inline void Mesh::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_IBO);

			bind();

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), m_Indices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			glEnableVertexAttribArray(SHADER_POSITION_INDEX);

			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

			glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
            glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);

			unbind();
		}

		void Mesh::draw() const
		{
			glDrawElements(GL_LINE_LOOP, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
