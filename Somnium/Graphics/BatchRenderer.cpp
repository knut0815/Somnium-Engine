#include "BatchRenderer.h"

#define MAX_VERTICES 1000000

namespace Somnium
{
	namespace Graphics
	{
		void BatchRenderer::flushQueue()
		{
			while (!m_RenderQueue.empty()) {
				RenderableObject* object = m_RenderQueue.front();
				m_RenderQueue.pop();

				const std::vector<Mesh*> meshes = object->getMeshes();

				for (Mesh* mesh : meshes)
				{
					mesh->bind();
					mesh->getShader().enable();

					mesh->getShader().setMatrix4("projectionMatrix", m_Camera.getProjection());
					mesh->getShader().setMatrix4("viewMatrix", m_Camera.getView());
					mesh->getShader().setMatrix4("modelMatrix", mesh->getModelMatrix());

					glDrawElements(GL_LINE_LOOP, (GLsizei)mesh->getIBOSize(), GL_UNSIGNED_SHORT, nullptr);

					mesh->getShader().disable();
					mesh->unbind();
				}
			}
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

			glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
			glEnableVertexAttribArray(SHADER_POSITION_INDEX);

			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

			glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, texCoords));
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

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLushort), m_Indices.data(), GL_DYNAMIC_DRAW);
			glBindVertexArray(NULL);
		}

		void BatchRenderer::beginMapping()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_VertexDataBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::submitToQueue(RenderableObject* object)
		{
			Vertex vert = object->getMeshes().front()->getVertices()->front();
			Maths::Vector3& pos = vert.position;

			if(m_VertexDataBuffer)
				m_VertexDataBuffer->position = pos;

			m_VertexDataBuffer++;
		}

		void BatchRenderer::endMapping()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}
	}
}