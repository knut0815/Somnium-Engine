#pragma once
#include <glew.h>

namespace LKREngine 
{
	namespace Graphics 
	{
		class Buffer
		{
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			inline GLuint GetComponentCount() const { return m_ComponentCount; }
			inline void Bind() const;
			inline void Unbind() const;

		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;
		};
	}
}