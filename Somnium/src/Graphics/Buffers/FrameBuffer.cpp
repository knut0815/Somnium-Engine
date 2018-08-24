#include "FrameBuffer.h"

#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			Window const* FrameBuffer::s_Window;

			void FrameBuffer::setWindow(Window const * window) { s_Window = window; }

			FrameBuffer::FrameBuffer(unsigned int noOfColourBuffers, bool enableDepthBuffer, unsigned int startXCoord, unsigned int startYCoord, unsigned int endXCoord, unsigned int endYCoord)
			: m_NoOfColourBuffers(noOfColourBuffers), m_ColourBuffers(new GLuint[m_NoOfColourBuffers]), m_StartX(startXCoord), m_StartY(startYCoord), m_EndX(endXCoord), m_EndY(endYCoord)
			{
				glGenFramebuffers(1, &m_BufferID);

				bind();

				initColourBuffers();

				if(enableDepthBuffer) initDepthBuffer();

				int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

				if(status != GL_FRAMEBUFFER_COMPLETE)
				       std::cerr << "FRAMEBUFFER ERROR: " << status << std::endl;

				unbind();
			}

			void FrameBuffer::initColourBuffers()
			{
				glGenTextures(m_NoOfColourBuffers, m_ColourBuffers);

				for (unsigned int i = 0; i < m_NoOfColourBuffers; i++)
				{
					glBindTexture(GL_TEXTURE_2D, m_ColourBuffers[i]);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, s_Window->getWidth(), s_Window->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //TODO Make screen height/size alterable

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

					m_Attachments.push_back(GL_COLOR_ATTACHMENT0 + i);

					glFramebufferTexture2D(GL_FRAMEBUFFER, m_Attachments.at(i), GL_TEXTURE_2D, m_ColourBuffers[i], 0);
				}

				glBindTexture(GL_TEXTURE_2D, 0);
			}

			void FrameBuffer::initDepthBuffer()
			{
				glGenTextures(1, &m_DepthTexture);

				glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, s_Window->getWidth(), s_Window->getHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); //TODO Make screen height/size alterable

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				m_Attachments.push_back(GL_DEPTH_ATTACHMENT);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);
			}

			void FrameBuffer::draw() const
			{
				glDrawBuffers(m_NoOfColourBuffers, m_Attachments.data());
			}
		}
	}
}
