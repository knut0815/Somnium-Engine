#pragma once

#include "PostProcessingUnit.h"
#include "../Shaders/Shader.h"
#include "PostProcessor.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
				class Filter
				: public PostProcessingUnit
				  {
				  public:
					Filter(std::string vertexShaderFilepath, std::string fragmentShaderFilepath)
				  : Filter(vertexShaderFilepath.c_str(), fragmentShaderFilepath.c_str()) {}

					Filter(const char* vertexShaderFilepath, const char* fragmentShaderFilepath)
				  : s_Shader(new Shaders::Shader(vertexShaderFilepath, fragmentShaderFilepath)){}

					static void initialise();
					void Process(Buffers::FrameBuffer* toProcess);

				  public:
					static Filter *greyscale, *sepia, *brightFilter;

				  private:
					virtual ~Filter(){};
					static bool s_Initialised;

					Shaders::Shader* s_Shader;
				  };
		}
	}
}
