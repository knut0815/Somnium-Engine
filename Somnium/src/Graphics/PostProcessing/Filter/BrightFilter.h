#pragma once

#include "../PostProcessingUnit.h"
#include "../../Shaders/Shader.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			namespace Filter
			{
				class BrightFilter
				: public PostProcessingUnit
				{
					public:
						static PostProcessingUnit* getInstance()
						{
							static BrightFilter instance;

							if (s_Shader == nullptr)
								s_Shader = new Shaders::Shader("Resources/Graphics/Shaders/Basic/passthrough2D.vs","Resources/Graphics/Shaders/Post-Processing/Filters/brightnessFilter.fs");

							return &instance;
						}

						void Process(Buffers::FrameBuffer* toProcess);

						virtual ~BrightFilter() {};

					private:
						BrightFilter() {};

					private:
						static Shaders::Shader* s_Shader;
				};

			}
		}
	}
}
