#include "Mesh.h"

namespace Somnium
{
	namespace Graphics
	{
		Mesh::Mesh(Buffers::VertexArray* vertexArray, Buffers::IndexBuffer* indexBuffer, std::vector<Texture> textures, Shader& shader)
			: m_Textures(textures), m_Shader(shader), m_VAO(vertexArray), m_IBO(indexBuffer)
		{
			
		}

		Mesh::Mesh(std::vector<GLfloat> vertexArray, std::vector<GLushort> indexBuffer, std::vector<Texture> textures, Shader& shader)
			: m_Textures(textures), m_Shader(shader), m_VertexData(vertexArray), m_IndexData(indexBuffer)
		{

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

		const Maths::Matrix4 Mesh::getModelMatrix() const
		{	
			return 
			  Maths::Matrix4::rotationX(m_Orientation.x)
			* Maths::Matrix4::rotationY(m_Orientation.y)
			* Maths::Matrix4::rotationZ(m_Orientation.z)
			* const_cast<Maths::Matrix4&>(m_ModelMatrix);
		}
	}
}