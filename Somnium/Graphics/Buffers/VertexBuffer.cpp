#include "VertexBuffer.h"

namespace Somnium
{
	namespace Graphics 
	{
		namespace Buffers
		{
		VertexBuffer::VertexBuffer(GLfloat* data, size_t dataPointCount, GLuint componentCount)
			: m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_BufferID);
			bind();
			glBufferData(GL_ARRAY_BUFFER, dataPointCount * componentCount * sizeof(GLfloat), data, GL_STATIC_DRAW);
			unbind();
		}

		VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_BufferID); }

		void VertexBuffer::bind()   const { glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); }
		void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		}
	}
}