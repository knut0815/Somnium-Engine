#pragma once

#include "PostProcessingUnit.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			class Bloom
			: public PostProcessingUnit
			{
				public:
					virtual ~Bloom();

					static PostProcessingUnit& getInstance()
					{
						static Bloom instance;

						if(s_Shader == nullptr)
							 s_Shader = new Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert", "Resources/Graphics/Shaders/GL/Post-Processing/bloom.frag");

						return instance;
					}

					void Process(Buffers::FrameBuffer* toProcess);
				private:
					Bloom();

				private:
					static Shaders::Shader* s_Shader;
			};

		}
	}
}
