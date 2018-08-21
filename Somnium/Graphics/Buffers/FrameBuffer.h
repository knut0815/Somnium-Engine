#pragma once

#include "Buffer.h"

namespace Somnium {
	namespace Graphics {
		namespace Buffers {
			class FrameBuffer
					: public Buffer{
				public:
					FrameBuffer();
					virtual ~FrameBuffer();

			};

		}
	}
}
