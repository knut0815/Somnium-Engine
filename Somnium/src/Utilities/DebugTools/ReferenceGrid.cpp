#include "ReferenceGrid.h"

namespace Somnium
{
	namespace Utilities
	{
		namespace Debug
		{
			namespace Tools
			{
				void ReferenceGrid::draw()
				{
					m_Shader.enable();
					m_VAO.bind();

					glDrawArrays(GL_LINES, 0, m_VertexData.size());

					m_VAO.unbind();
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

					m_VBO = new Graphics::Buffers::VertexBuffer(m_VertexData, vertexPoints.size(), 3);
				}
			}
		}
	}
}
