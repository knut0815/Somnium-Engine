#pragma once

#include "Renderer.h"

namespace Somnium
{
	namespace Graphics
	{
		class BatchRenderer : virtual Renderer
		{
		public:
			BatchRenderer(const Window& window, Camera camera)
				: Renderer(window, camera){};
			
			virtual void flushQueue();
			virtual void submitToQueue(RenderableObject* object);
			virtual void updateCamera();
		};
	}
}