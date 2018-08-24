#include "RenderBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			RenderBuffer::RenderBuffer()
			{
				glGenRenderbuffers(1, &m_BufferID);

				bind();

				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_BufferID);

				unbind();
			}
		}
	}
}
