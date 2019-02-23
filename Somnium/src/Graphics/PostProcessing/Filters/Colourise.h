#pragma once

#include "Filter.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			namespace Filters
			{
				class Colourise
					: public Filter
				{
				public:
					static Colourise* apply(float red, float green, float blue, float strength);
					virtual ~Colourise() {};

				protected:
					Colourise()
						: Filter("Resources/Graphics/Shaders/Basic/passthrough2D.vs", "Resources/Graphics/Shaders/Post-Processing/Filters/Colour/colourise.fs") {};

				private:
					static Colourise* s_Instance;
				};
			}
		}
	}
}