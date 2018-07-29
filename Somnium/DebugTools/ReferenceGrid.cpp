#include "ReferenceGrid.h"

namespace Somnium
{
	namespace DebugTools
	{
		void ReferenceGrid::draw()
		{
			m_Shader.enable();
			m_VAO.bind();

			Maths::Matrix4 m_ModelMatrix = Maths::Matrix4::identity();
			m_ModelMatrix *= Maths::Matrix4::translation(Maths::Vector3(0, 0, 0));

			Maths::Matrix4 finalisedMatrix = Maths::Matrix4::identity();

			finalisedMatrix *= Maths::Matrix4::rotationX(0);
			finalisedMatrix *= Maths::Matrix4::rotationY(0);
			finalisedMatrix *= Maths::Matrix4::rotationZ(0);
			finalisedMatrix *= m_ModelMatrix;

			glDrawArrays(GL_LINES,0, m_VertexData.size());

			m_VAO.unbind();
			m_Shader.disable();
		}

		void ReferenceGrid::setGridSize(float size)
		{
			m_GridSize = size;
			updateSquares();
		}

		void ReferenceGrid::setDivision(float size)
		{
			m_DivisionSize = size;
			updateSquares();
		}

		void ReferenceGrid::init()
		{
			updateSquares();

			std::vector<Maths::Vector3> vertexPoints;

			for (int x = -m_xSquares / 2; x <= m_xSquares / 2; x++)
			{
				vertexPoints.push_back(Maths::Vector3(x * m_DivisionSize, 0, -m_GridSize.x / 2));
				vertexPoints.push_back(Maths::Vector3(x * m_DivisionSize, 0, m_GridSize.x / 2));

				vertexPoints.push_back(Maths::Vector3(-m_GridSize.y / 2, 0, x * m_DivisionSize));
				vertexPoints.push_back(Maths::Vector3(m_GridSize.y / 2, 0, x * m_DivisionSize));
			}

			vertexPoints.push_back(Maths::Vector3(0, m_GridSize.z / 2, 0));
			vertexPoints.push_back(Maths::Vector3(0, -m_GridSize.z / 2, 0));

			for (Maths::Vector3 point : vertexPoints)
			{
				m_VertexData.push_back(point.x);
				m_VertexData.push_back(point.y);
				m_VertexData.push_back(point.z);
			}

			m_VBO = new Graphics::Buffers::VertexBuffer(m_VertexData, vertexPoints.size(),3);
		}
	}
}