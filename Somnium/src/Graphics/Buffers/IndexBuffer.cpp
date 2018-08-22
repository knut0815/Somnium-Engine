#include "IndexBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			IndexBuffer::IndexBuffer(GLushort* data, size_t count)
				:m_Count(count)
			{
				glGenBuffers(1, &m_BufferID);
				bind();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
				unbind();
			}
		}
	}
}
