#pragma once

#include "../Shaders/Shader.h"
#include "../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			class PostProcessingUnit
			  {
			  public:
				virtual ~PostProcessingUnit(){};
				virtual void Process(Buffers::FrameBuffer* toProcess) = 0;

			  protected:
				PostProcessingUnit(){};
			  };
		}
	}
}
