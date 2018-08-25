#pragma once

#include "PostProcessingUnit.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
			{
				class GaussianBlur
				: public PostProcessingUnit
				{
					public:
						static PostProcessingUnit* const getInstance()
						{
							static GaussianBlur instance;

							if(s_Shader == nullptr)
								s_Shader = new Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert", "Resources/Graphics/Shaders/GL/Post-Processing/gaussianBlur.frag");

							return &instance;
						}

						~GaussianBlur();

						void Process(Buffers::FrameBuffer* toProcess);

					private:
						GaussianBlur();

					private:
						static Shaders::Shader* s_Shader;
				};
		}
	}
}
