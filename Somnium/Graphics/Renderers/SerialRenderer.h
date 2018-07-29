#pragma once
#include <vector>
#include <queue>
#include "../RenderableObject.h"
#include "../Camera.h"
#include "../Window.h"
#include "Renderer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			class SerialRenderer
				: virtual public Renderer
			{
				/* Methods */
			public:
				SerialRenderer(const Window& window, Camera& const camera)
					: Renderer(window, camera) {};
				virtual void submitToQueue(RenderableObject* object) { m_RenderQueue.push(object); }
				virtual void flushQueue();

			private:
				std::queue<RenderableObject*> m_RenderQueue;
			};
		}
	}
}