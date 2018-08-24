#pragma once

#include "Buffer.h"
#include "RenderBuffer.h"
#include "../Window.h"

#include <vector>

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
					FrameBuffer(unsigned int noOfColourBuffers = 1, bool enableDepthBuffer = true, unsigned int startXCoord = 0, unsigned int startYCoord = 0, unsigned int endXCoord = s_Window->getWidth(), unsigned int endYCoord = s_Window->getHeight());
					~FrameBuffer()
					{
						glDeleteFramebuffers(1, &m_BufferID);
						glDeleteTextures(m_NoOfColourBuffers, m_ColourBuffers);
						delete[] m_ColourBuffers;
					}

					void draw() const;

					inline void bind() const
					{
						glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
						glViewport(m_StartX, m_StartY, m_EndX, m_EndY);
					}

					inline void unbind() const
					{
						glBindFramebuffer(GL_FRAMEBUFFER, 0);
						glViewport(0, 0, s_Window->getWidth(), s_Window->getHeight());
					}

					inline void clear() const
					{
						bind();

						glClearColor(0.f, 0.f, 0.f, 1.f);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

						unbind();
					}

					inline void bindColourTexture(const unsigned int& textureSlot = 0, const unsigned int& colourAttachment = 0) const
					{
						glActiveTexture(GL_TEXTURE0 + textureSlot);
						glBindTexture(GL_TEXTURE_2D, m_ColourBuffers[colourAttachment]);
						glActiveTexture(GL_TEXTURE0);
					}

					inline void bindDepthTexture(const unsigned int& textureSlot = 0) const
					{
						glActiveTexture(GL_TEXTURE0 + textureSlot);
						glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
						glActiveTexture(GL_TEXTURE0);
					}

					GLuint getColourTexture(unsigned int index = 0) const { return index < m_NoOfColourBuffers ? m_ColourBuffers[index] : 0; }
					GLuint getDepthTexture() const { return m_DepthTexture; }

					static void setWindow(Window const * window);

				private:
					void initColourBuffers();
					void initDepthBuffer();

				private:
					unsigned int m_StartX, m_StartY, m_EndX, m_EndY;
					GLuint m_BufferID = 0;
					GLuint const m_NoOfColourBuffers;
					GLuint* const m_ColourBuffers;
					GLuint m_DepthTexture = 0;
					//Buffers::RenderBuffer m_DepthBuffer;
					std::vector<GLuint> m_Attachments;
					static Window const * s_Window;
			};
		}
	}
}
