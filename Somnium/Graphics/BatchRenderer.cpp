#include "BatchRenderer.h"

#define MAX_VERTICES 1000000

namespace Somnium
{
	namespace Graphics
	{
		void BatchRenderer::flushQueue()
		{

		}

		void BatchRenderer::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_IBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			glEnableVertexAttribArray(SHADER_POSITION_INDEX);

			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

			glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);

			glBindBuffer(GL_ARRAY_BUFFER, NULL);

			unsigned int offset = 0;

			for(unsigned int i = 0; i < 100000; i += 6) //TODO: Make the number variable
			{
				for(unsigned int ind = 0; ind < 2; ind++)
					m_Indices.push_back(offset + ind);
				for (unsigned int ind = 2; ind <= 4; ind++)
					m_Indices.push_back(offset + (ind % 4));
				
				offset += 4;
			}

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLushort), m_Indices.data(), GL_STATIC_DRAW);
			glBindVertexArray(NULL);
		}

		void BatchRenderer::submitToQueue(RenderableObject* object)
		{

		}

		void BatchRenderer::updateCamera()
		{

		}
	}
}