#include "VertexArray.h"

namespace LKREngine
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayID);
		}

		VertexArray::~VertexArray() 
		{
			for (Buffer* buffer : m_Buffers)
				delete buffer;

			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VertexArray::AddBuffer(Buffer* buffer, GLuint index) 
		{
			Bind();
			buffer->Bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			
			buffer->Unbind();
			Unbind();
		}

		void VertexArray::Bind() const 
		{
			glBindVertexArray(m_ArrayID);
		}

		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}
	}
}