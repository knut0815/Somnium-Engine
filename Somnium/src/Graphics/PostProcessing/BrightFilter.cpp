#include "BrightFilter.h"
#include "PostProcessor.h"
#include "../Shaders/Shader.h"
#include "../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			Shaders::Shader* BrightFilter::s_Shader = nullptr;

			BrightFilter::BrightFilter()
			{

			}

			BrightFilter::~BrightFilter()
			{

			}

			void BrightFilter::Process(Buffers::FrameBuffer* toProcess)
			{

			}
		}
	}
}
