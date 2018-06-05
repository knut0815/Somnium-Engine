#include "VertexArray.h"

#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			VertexArray::VertexArray() { glGenVertexArrays(1, &m_ArrayID); }

			VertexArray::~VertexArray()
			{
				for (VertexBuffer* buffer : m_Buffers) delete buffer;
				glDeleteVertexArrays(1, &m_ArrayID);
			}

			void VertexArray::addBuffer(VertexBuffer* buffer, GLuint index)
			{
				bind();
				buffer->bind();

				glEnableVertexAttribArray(index);

				glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

				buffer->unbind();
				unbind();

				m_Buffers.push_back(buffer);
			}

			void VertexArray::bind()   const { glBindVertexArray(m_ArrayID); }
			void VertexArray::unbind() const { glBindVertexArray(0); }
		}
	}
}