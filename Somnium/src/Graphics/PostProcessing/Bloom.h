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

					static PostProcessingUnit* const getInstance()
					{
						static Bloom instance;

						if(s_Shader == nullptr){
							 s_Shader = new Shaders::Shader("Resources/Graphics/Shaders/Basic/passthrough2D.vs", "Resources/Graphics/Shaders/Post-Processing/bloom.fs");
							 s_Shader->setInt("original", 1);
							 s_Shader->setInt("blurred", 2);
							 s_Shader->setFloat("exposure", 1);
						}

						return &instance;
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
