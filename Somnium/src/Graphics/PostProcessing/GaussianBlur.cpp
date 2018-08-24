#include "GaussianBlur.h"
#include "PostProcessor.h"
#include "../Shaders/Shader.h"
#include "../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
				Shaders::Shader* GaussianBlur::s_Shader = nullptr;

				GaussianBlur::GaussianBlur()
				{

				}

				GaussianBlur::~GaussianBlur()
				{ }

				void GaussianBlur::Process(Buffers::FrameBuffer* toProcess)
				{
					s_Shader->enable();
					bool horz = true;

					static Buffers::FrameBuffer tempFBO[2];

					for(unsigned int i = 0; i < 10; i++){
							s_Shader->setInt("horizontal", horz);
							tempFBO[horz].clear();
							tempFBO[horz].bind();
							i == 0 ? toProcess->bindColourTexture() : tempFBO[!horz].bindColourTexture();

							Graphics::PostProcessing::PostProcessor::drawScreen(s_Shader);

							horz = !horz;
					}

					toProcess->clear();
					toProcess->bind();
					tempFBO[!horz].bindColourTexture();
					Graphics::PostProcessing::PostProcessor::drawScreen();
					toProcess->unbind();
				}
		}
	}
}
