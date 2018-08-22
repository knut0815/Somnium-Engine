#pragma once

#include "Buffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class FrameBuffer
					: public Buffer
					  {
				public:
					FrameBuffer();
					virtual ~FrameBuffer() { glDeleteFramebuffers(1, &m_BufferID); }

					inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID); }
					inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

				private:
					GLuint m_BufferID = 0;
			};
		}
	}
}
