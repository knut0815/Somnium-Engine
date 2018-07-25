#pragma once

#include "../Window.h"
#include "../Camera.h"
#include "../RenderableObject.h"
#include <queue>
#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			class Renderer
			{
			public:
				Renderer(const Window& window, const Camera camera)
					: m_Window(window), m_Camera(camera) {};

				virtual void flushQueue() = 0;

				virtual void submitToQueue(RenderableObject* object) = 0;
				void updateCamera()
				{
					//Process Keyboard input

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

					Maths::Vector3 cameraPos = m_Camera.getPosition();
					Maths::Vector3 cameraDeg = m_Camera.getOrientation();

					//Process Mouse Input
					/* Stage 1: Scroll Wheel */

					static int prevXScrollOffset, prevYScrollOffset, xScrollOffset = 0, yScrollOffset = 0;

					prevXScrollOffset = xScrollOffset;
					prevYScrollOffset = yScrollOffset;

					m_Window.getMouseScroll(xScrollOffset, yScrollOffset);

					if (prevYScrollOffset < yScrollOffset)
						m_Camera.offsetFOV(1);
					else if (prevYScrollOffset > yScrollOffset)
						m_Camera.offsetFOV(-1);

					/* Stage 2: X/Y Offset */
					static int mouseX = m_Window.getWidth() / 2, mouseY = m_Window.getHeight() / 2, prevMouseX, prevMouseY, xOffset, yOffset;

					prevMouseX = mouseX;
					prevMouseY = mouseY;

					m_Window.getMousePosition(mouseX, mouseY);

					xOffset = mouseX - prevMouseX;
					yOffset = prevMouseY - mouseY;

					m_Camera.offsetOrientation(yOffset, xOffset);
					m_Camera.updateUI();
				}

			protected:
				Camera m_Camera;
				const Window& m_Window;
			};
		}
	}
}
