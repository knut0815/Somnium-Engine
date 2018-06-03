#include "BatchRenderer.h"

#define MAX_VERTICES 1000000
#define INDEX_AMOUNT MAX_VERTICES * 3

namespace Somnium
{
	namespace Graphics
	{

		void BatchRenderer::flushQueue()
		{
			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_SHORT, NULL);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
			glBindVertexArray(NULL);

			m_CurrentIndex = 0;
		}

		void BatchRenderer::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
			glEnableVertexAttribArray(SHADER_POSITION_INDEX);

			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

			glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);

			glBindBuffer(GL_ARRAY_BUFFER, NULL);

			unsigned int offset = 0;

			for(unsigned int i = 0; i < INDEX_AMOUNT; i += 6) //TODO: Make the number variable
			{
				for(unsigned int ind = 0; ind < 2; ind++)
					m_Indices.push_back(offset + ind);
				for (unsigned int ind = 2; ind <= 4; ind++)
					m_Indices.push_back(offset + (ind % 4));
				
				offset += 4;
			}

//			m_IBO = new IndexBuffer(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));

			glBindVertexArray(NULL);
		}

		void BatchRenderer::beginMapping()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_VertexDataBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::submitToQueue(RenderableObject* object)
		{
			const Maths::Vector3& pos = object->getMeshes().front()->getVertices()->front().position;

			if (m_VertexDataBuffer) {
				m_VertexDataBuffer->position = pos;
				m_CurrentIndex++;
			}

			
			m_VertexDataBuffer ++;
		}

		void BatchRenderer::endMapping()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, NULL);
		}
	}
}