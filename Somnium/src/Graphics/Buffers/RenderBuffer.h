#pragma once

#include "Buffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class RenderBuffer
					: public Buffer
			{
				public:
					RenderBuffer();
					~RenderBuffer() { glDeleteRenderbuffers(1, &m_BufferID); }

					inline void bind() const { glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID); }
					inline void unbind() const { glBindRenderbuffer(GL_RENDERBUFFER, 0); }

				private:
					GLuint m_BufferID = 0;
			};
		}
	}
}
