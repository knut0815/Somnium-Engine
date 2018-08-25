#pragma once

#include "PostProcessingUnit.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			class BrightFilter
			: public PostProcessingUnit
			{
			public:
				static PostProcessingUnit* const getInstance()
				{
					static BrightFilter instance;

					if (s_Shader == nullptr)
						 s_Shader = new Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert","Resources/Graphics/Shaders/GL/Post-Processing/Filters/brightnessFilter.frag");

					return &instance;
				}

				void Process(Buffers::FrameBuffer* toProcess);

				virtual ~BrightFilter();

			private:
				BrightFilter();

			private:
				static Shaders::Shader* s_Shader;
			};

		}
	}
}
