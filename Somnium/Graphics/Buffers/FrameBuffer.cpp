#include "FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			FrameBuffer::FrameBuffer(unsigned int noOfColourBuffers)
			: m_NoOfColourBuffers(noOfColourBuffers), m_Attachments(new GLuint[m_NoOfColourBuffers])
			{
				glGenFramebuffers(1, &m_BufferID);

				bind();

				GLuint colourBuffers[noOfColourBuffers];
				glGenTextures(noOfColourBuffers, colourBuffers);

				for (unsigned int i = 0; i < noOfColourBuffers; i++)
				{
					glBindTexture(GL_TEXTURE_2D, colourBuffers[i]);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1920, 1080, 0, GL_RGB, GL_FLOAT, NULL); //TODO Make screen height/size alterable

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

					m_Attachments[i] = GL_COLOR_ATTACHMENT0 + i;

					glFramebufferTexture2D(GL_FRAMEBUFFER, m_Attachments[i], GL_TEXTURE_2D, colourBuffers[i], 0);
				}

				unbind();
			}

			void FrameBuffer::draw() const
			{
				bind();

				glDrawBuffers(m_NoOfColourBuffers, m_Attachments);

				unbind();
			}
		}
	}
}
