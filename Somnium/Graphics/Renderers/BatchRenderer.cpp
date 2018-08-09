#include "BatchRenderer.h"

#include "../Buffers/IndexBuffer.h"
#include <iostream>

#define MAX_VERTICES 100000
#define INDEX_AMOUNT MAX_VERTICES * 3

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			BatchRenderer::~BatchRenderer()
			{
				delete m_VAO;
				delete m_VBO;
				delete m_IBO;
			}

			void BatchRenderer::flushQueue()
			{
				if (m_CurrentIndex == 0 || m_CurrentVertexCount == 0) return;

				m_VAO->bind();
				m_IBO->bind();

				m_VAO->draw(m_CurrentIndex);

				m_IBO->unbind();
				m_VAO->unbind();

				m_CurrentIndex = 0;
				m_CurrentVertexCount = 0;
			}

			void BatchRenderer::init()
			{
				m_VAO = new Buffers::VertexArray();
				m_VBO = new Buffers::VertexBuffer(NULL, MAX_VERTICES * sizeof(GLfloat), 3, GL_DYNAMIC_DRAW);

				m_VAO->addBuffer(m_VBO, SHADER_POSITION_INDEX);

				/*
				glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

				glVertexAttribPointer(SHADER_TEXTURE_COORDINATE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, texCoords));
				glEnableVertexAttribArray(SHADER_TEXTURE_COORDINATE_INDEX);
				*/

				unsigned int offset = 0;

				std::vector<GLushort> indices;

				for (unsigned int i = 0; i < INDEX_AMOUNT; i += 6) //TODO: Make the number variable
				{
					for (unsigned int ind = 0; ind < 2; ind++)
						indices.push_back(offset + ind);
					for (unsigned int ind = 2; ind <= 4; ind++)
						indices.push_back(offset + (ind % 4));

					offset += 4;
				}

				m_IBO = new Buffers::IndexBuffer(indices, INDEX_AMOUNT);
			}

			void BatchRenderer::beginMapping()
			{
				m_VBO->bind();
#ifndef WEB_BUILD
				m_VertexDataBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#else
				//TODO: glSubData version
#endif
			}

			void BatchRenderer::submitToQueue(RenderableObject* object)
			{
				const std::vector<GLfloat>& test = object->getMesh()->getVertexData();

				if (m_CurrentVertexCount + test.size() >= MAX_VERTICES)
				{
					cerr << "ERROR: BATCH FULL - CANNOT ADD MORE VERTICES!" << endl;
					return; //Too many vertices
				}

				for (GLfloat vertex : test)
				{
					*(m_VertexDataBuffer++) = vertex;
				}

				m_CurrentVertexCount += test.size();
				m_CurrentIndex += test.size() / 3;
			}

			void BatchRenderer::endMapping()
			{
				glUnmapBuffer(GL_ARRAY_BUFFER);
				m_VBO->unbind();
			}
		}
	}
}
