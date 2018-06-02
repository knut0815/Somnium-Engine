#pragma once
#include <vector>
#include <queue>
#include "RenderableObject.h"
#include "Camera.h"
#include "Window.h"

namespace Somnium
{
	namespace Graphics
	{
		class Renderer 
		{
		/* Methods */
		public:
			Renderer(const Window& window, const Camera camera) : m_Window(window), m_Camera(camera) {};
			void submitToQueue(RenderableObject* object) { m_RenderQueue.push(object); };
			void flushQueue();
			void updateCamera();

		private:
			
		/* Variables */
		public:

		private:
			std::queue<RenderableObject*> m_RenderQueue;
			Camera m_Camera;
			const Window& m_Window;
		};
	}
}