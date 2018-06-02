#pragma once

#include "Window.h"
#include "Camera.h"
#include "RenderableObject.h"
#include <queue>

namespace Somnium
{
	namespace Graphics
	{
		class Renderer
		{
		public:
			Renderer();
			Renderer(const Window& window, Camera camera) : m_Window(window), m_Camera(camera) {};

			virtual void flushQueue() = 0;
			virtual void submitToQueue(RenderableObject* object) = 0;
			virtual void updateCamera() = 0;

		protected:
			std::queue<RenderableObject*> m_RenderQueue;
			Camera m_Camera;
			const Window& m_Window;
		};
	}
}