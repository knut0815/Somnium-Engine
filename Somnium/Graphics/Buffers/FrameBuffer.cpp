#include "FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			FrameBuffer::FrameBuffer()
			{
				glGenFramebuffers(1, &m_BufferID);
			}
		}
	}
}
