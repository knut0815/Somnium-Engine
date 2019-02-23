#include "Bloom.h"
#include "../PostProcessor.h"
#include "../../Shaders/Shader.h"
#include "../../Buffers/FrameBuffer.h"
#include "../Distortion/GaussianBlur.h"
#include "../Filters/Filter.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
		namespace Lighting
		{
			Shaders::Shader* Bloom::s_Shader = nullptr;

			void Bloom::Process(Buffers::FrameBuffer* toProcess)
			{
				static Buffers::FrameBuffer blurred, bloom;

				blurred.bind();

				toProcess->bindColourTexture();
				Graphics::PostProcessing::PostProcessor::drawScreen();

				Filter::brightFilter->Process(&blurred);
				Distortion::GaussianBlur::getInstance()->Process(&blurred);

				bloom.bind();
				toProcess->bindColourTexture(1);
				blurred.bindColourTexture(2);
				Graphics::PostProcessing::PostProcessor::drawScreen(s_Shader);

				toProcess->bind();
				bloom.bindColourTexture();
				Graphics::PostProcessing::PostProcessor::drawScreen();

				toProcess->unbind();
			}
			}
		}
	}
}
