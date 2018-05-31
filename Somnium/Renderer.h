#pragma once
#include <vector>
#include "Renderable.h"

namespace Somnium
{
	namespace Graphics
	{
		class Renderer 
		{
		/* Methods */
		public:
			Renderer() {};
			~Renderer() {};
		private:
			
		/* Variables */
		public:

		private:
			const std::vector<Renderable> objects;
		};
	}
}