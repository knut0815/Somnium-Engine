#pragma once

namespace Somnium
{
	namespace Graphics
	{
		class Renderable
		{
		/* Methods */
		public:


			virtual void draw() = 0;
			virtual void update() = 0;
		};
	}
}