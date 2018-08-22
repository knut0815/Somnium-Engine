#include "FrameBuffer.h"

#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			FrameBuffer::FrameBuffer(unsigned int noOfColourBuffers)
			: m_NoOfColourBuffers(noOfColourBuffers)
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

					m_Attachments.push_back(GL_COLOR_ATTACHMENT0 + i);

					glFramebufferTexture2D(GL_FRAMEBUFFER, m_Attachments.at(i), GL_TEXTURE_2D, colourBuffers[i], 0);
				}
				int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

				if(status != GL_FRAMEBUFFER_COMPLETE)
				       std::cerr << "FRAMEBUFFER ERROR: " << status << std::endl;

				unbind();
			}

			void FrameBuffer::draw() const
			{
				glDrawBuffers(m_NoOfColourBuffers, m_Attachments.data());
			}
		}
	}
}
