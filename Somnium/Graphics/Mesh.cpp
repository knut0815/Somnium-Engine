#include "Mesh.h"

namespace Somnium
{
	namespace Graphics
	{
		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Shader& shader)
			: m_Vertices(vertices), m_Indices(indices), m_Textures(textures), m_Shader(shader)
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

		Maths::Matrix4 Mesh::getModelMatrix()
		{
			Maths::Matrix4 modelMatrix = Maths::Matrix4::identity();

			modelMatrix *= Maths::Matrix4::rotationX(m_Orientation.x);
			modelMatrix *= Maths::Matrix4::rotationY(m_Orientation.y);
			modelMatrix *= Maths::Matrix4::rotationZ(m_Orientation.z);
			modelMatrix *= Maths::Matrix4::translation(m_Position);
			modelMatrix *= Maths::Matrix4::scale(m_Scale);

			return modelMatrix;
		}
	}
}
