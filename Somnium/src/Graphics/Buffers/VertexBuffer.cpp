#include "VertexBuffer.h"

namespace Somnium
{
	namespace Graphics 
	{
		namespace Buffers
		{
		VertexBuffer::VertexBuffer(GLfloat* data, size_t dataPointCount, GLuint componentCount, GLuint drawMode)
			: m_DrawMode(drawMode), m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ARRAY_BUFFER, dataPointCount * componentCount * sizeof(GLfloat), data, m_DrawMode);
			unbind();
		}

		VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_BufferID); }
		}
	}
}
