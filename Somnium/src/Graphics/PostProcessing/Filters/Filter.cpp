#include "Filter.h"
#include "../PostProcessor.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing	
		{
			Filter *Filter::greyscale, *Filter::sepia, *Filter::brightFilter;
			bool Filter::s_Initialised;

			void Filter::Process(Buffers::FrameBuffer* toProcess)
			{
				static Buffers::FrameBuffer fbo;

				fbo.clear();
				fbo.bind();
				toProcess->bindColourTexture();
				PostProcessor::drawScreen(s_Shader);

				toProcess->clear();
				toProcess->bind();
				fbo.bindColourTexture();
				PostProcessor::drawScreen();
				toProcess->unbind();
			}

			void Filter::initialise()
			{
				if(s_Initialised) return;
				greyscale = new Filter("Resources/Graphics/Shaders/Basic/passthrough2D.vs","Resources/Graphics/Shaders/Post-Processing/Filters/Colour/greyscale.fs");
				sepia = new Filter("Resources/Graphics/Shaders/Basic/passthrough2D.vs","Resources/Graphics/Shaders/Post-Processing/Filters/Colour/sepia.fs");
				brightFilter = new  Filter("Resources/Graphics/Shaders/Basic/passthrough2D.vs","Resources/Graphics/Shaders/Post-Processing/Filters/brightnessFilter.fs");

				s_Initialised = true;
			}
		}
	}
}
