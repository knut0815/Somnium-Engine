#include "Bloom.h"
#include "PostProcessor.h"
#include "../Shaders/Shader.h"
#include "../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			Shaders::Shader* Bloom::s_Shader = nullptr;

			Bloom::Bloom()
			{
				s_Shader->setInt("original", 1);
				s_Shader->setInt("blurred", 2);
				s_Shader->setFloat("exposure", 1);
			}

			Bloom::~Bloom()
			{

			}

			void Bloom::Process(Buffers::FrameBuffer* toProcess)
			{
				Buffers::FrameBuffer fbo;
				fbo.bind();

				toProcess->bindColourTexture(1,0);
				toProcess->bindColourTexture(2,1);

				Graphics::PostProcessing::PostProcessor::drawScreen();

				toProcess->bind();
				fbo.bindColourTexture();
				Graphics::PostProcessing::PostProcessor::drawScreen();
				toProcess->unbind();
			}
		}
	}
}
