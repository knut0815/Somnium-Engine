#include "PostProcessor.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			Graphics::Buffers::VertexArray* PostProcessor::s_ScreenVAO = nullptr;
			Graphics::Buffers::IndexBuffer* PostProcessor::s_ScreenIBO = nullptr;
			Graphics::Shaders::Shader* PostProcessor::s_ScreenShader = nullptr;
			bool PostProcessor::s_Initialised = false;

			void PostProcessor::initialise()
			{
				if (s_Initialised) return;

				s_ScreenVAO = new Buffers::VertexArray();
				s_ScreenIBO = new Buffers::IndexBuffer( {0, 1, 2, 2, 3, 0} );
				s_ScreenShader = new Graphics::Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/texture2D.vert", "Resources/Graphics/Shaders/GL/Basic/texture2D.frag");

				float screen[] = {
								-1.0f, -1.0f,
								1.0f, -1.0f,
								1.0f, 1.0f,
								-1.0f, 1.0f
						};

				float screenTexCoords[] = {
									0, 0,
									1, 0,
									1, 1,
									0, 1
							};

				PostProcessor::s_ScreenVAO->addBuffer(new Buffers::VertexBuffer(screen, 4, 2, GL_STATIC_DRAW), SHADER_POSITION_INDEX);
				PostProcessor::s_ScreenVAO->addBuffer(new Buffers::VertexBuffer(screenTexCoords, 4, 2, GL_STATIC_DRAW), SHADER_TEXTURE_COORDINATE_INDEX);

				s_Initialised = true;
			}

			PostProcessor::PostProcessor()
			{

			}

			PostProcessor::~PostProcessor()
			{

			}

			void PostProcessor::drawScreen(Shaders::Shader* shader)
			{

				shader->enable();

				s_ScreenVAO->bind();
				s_ScreenIBO->bind();

				s_ScreenVAO->draw(s_ScreenIBO->getCount());

				s_ScreenIBO->unbind();
				s_ScreenVAO->unbind();
			}

			void PostProcessor::process()
			{
				start();

				while(!m_PostProcessingUnits.empty())
				{
					//m_PostProcessingUnits.front()-enable();

					m_PostProcessingUnits.pop();
				}

				end();
			}
		}
	}
}
