#pragma once

#include "Window.h"
#include "Camera.h"
#include "RenderableObject.h"
#include <queue>
#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		class Renderer
		{
		public:
			Renderer(const Window& window, Camera camera) 
				: m_Window(window), m_Camera(camera) {};

			virtual void flushQueue() = 0;

			virtual void submitToQueue(RenderableObject* object) = 0;
			void updateCamera()
			{
					if (m_Window.isKeyPressed(GLFW_KEY_LEFT) || m_Window.isKeyPressed(GLFW_KEY_A))
						m_Camera.move(Maths::Vector3(-0.01f, 0, 0));
					if (m_Window.isKeyPressed(GLFW_KEY_RIGHT) || m_Window.isKeyPressed(GLFW_KEY_D))
						m_Camera.move(Maths::Vector3(0.01f, 0, 0));
					if (m_Window.isKeyPressed(GLFW_KEY_UP) || m_Window.isKeyPressed(GLFW_KEY_W))
					{
						if (m_Window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || m_Window.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
							m_Camera.move(Maths::Vector3(0, 0.01f, 0));
						else
							m_Camera.move(Maths::Vector3(0, 0, -0.01f));
					}
					if (m_Window.isKeyPressed(GLFW_KEY_DOWN) || m_Window.isKeyPressed(GLFW_KEY_S))
					{
						if (m_Window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || m_Window.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
							m_Camera.move(Maths::Vector3(0, -0.01f, 0));
						else
							m_Camera.move(Maths::Vector3(0, 0, 0.01f));
					}

					static double prevXOff, prevYOff;
					static double xOff = 0, yOff = 0;
					
					prevXOff = xOff;
					prevYOff = yOff;
					
					m_Window.getMouseScroll(xOff, yOff);

					if (prevYOff < yOff)
						m_Camera.offsetFOV(1);
					else if (prevYOff > yOff)
						m_Camera.offsetFOV(-1);

					cout << m_Camera.getFOV() << endl;
			}

		protected:
			Camera m_Camera;
			const Window& m_Window;
		};
	}
}