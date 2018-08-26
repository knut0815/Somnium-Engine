#include "BrightFilter.h"
#include "../PostProcessor.h"
#include "../../Shaders/Shader.h"
#include "../../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			namespace Filter
			{
				Shaders::Shader* BrightFilter::s_Shader = nullptr;

				void BrightFilter::Process(Buffers::FrameBuffer* toProcess)
				{
					static Buffers::FrameBuffer fbo;

					fbo.clear();
					fbo.bind();
					toProcess->bindColourTexture();
					Graphics::PostProcessing::PostProcessor::drawScreen(s_Shader);

					toProcess->clear();
					toProcess->bind();
					fbo.bindColourTexture();
					Graphics::PostProcessing::PostProcessor::drawScreen();
					toProcess->unbind();
				}
			}
		}
	}
}
