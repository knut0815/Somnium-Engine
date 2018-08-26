#include "Greyscale.h"
#include "../PostProcessor.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			namespace Filter
			{
				Shaders::Shader* Greyscale::s_Shader = nullptr;

				void Greyscale::Process(Buffers::FrameBuffer* toProcess)
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
