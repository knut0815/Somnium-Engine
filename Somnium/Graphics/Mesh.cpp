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

		void Mesh::scale(float uniformScale)
		{
			scale(Maths::Vector3(uniformScale));
		}

		void Mesh::scale(float x, float y, float z)
		{
			scale(Maths::Vector3(x, y, z));
		}

		void Mesh::scale(Maths::Vector3 scaleAmount)
		{
			m_ModelMatrix *= Maths::Matrix4::scale(scaleAmount);
		}

		void Mesh::translate(float x, float y, float z)
		{
			translate(Maths::Vector3(x, y, z));
		}

		void Mesh::translate(Maths::Vector3 translation)
		{
			m_ModelMatrix *= Maths::Matrix4::translation(translation);
		}

		void Mesh::rotate(float angleX, float angleY, float angleZ)
		{
			rotate(Maths::Vector3(angleX, angleY, angleZ));
		}

		void Mesh::rotate(Maths::Vector3 rotation)
		{
			m_ModelMatrix *= Maths::Matrix4::rotationX(rotation.x);
			m_ModelMatrix *= Maths::Matrix4::rotationY(rotation.y);
			m_ModelMatrix *= Maths::Matrix4::rotationZ(rotation.z);
		}

		const Maths::Matrix4 Mesh::getModelMatrix()
		{
			Maths::Matrix4 finalisedMatrix = Maths::Matrix4::identity();

			finalisedMatrix *= Maths::Matrix4::rotationX(m_Orientation.x);
			finalisedMatrix *= Maths::Matrix4::rotationY(m_Orientation.y);
			finalisedMatrix *= Maths::Matrix4::rotationZ(m_Orientation.z);
			finalisedMatrix *= m_ModelMatrix;

			return finalisedMatrix;
		}
	}
}
