#pragma once
#include <glew.h>

namespace LKREngine
{
	namespace Graphics
	{
		class IndexBuffer
		{
		public:
			IndexBuffer(GLushort*, GLsizei);
			~IndexBuffer();
			
			inline GLuint GetCount() const { return m_Count; }
			inline void Bind() const;
			inline void Unbind() const;

		private:
			GLuint m_BufferID;
			GLuint m_Count;
		};
	}
}