#pragma once
#include <vector>
#include <queue>
#include "RenderableObject.h"
#include "Camera.h"
#include "Window.h"
#include "Renderer.h"

namespace Somnium
{
	namespace Graphics
	{
		class SerialRenderer : virtual Renderer
		{
		/* Methods */
		public:
			SerialRenderer(const Window& window, const Camera camera) 
				: Renderer(window, camera) {};
			virtual void submitToQueue(RenderableObject* object) { m_RenderQueue.push(object); };
			virtual void flushQueue();
			virtual void updateCamera();
		};
	}
}