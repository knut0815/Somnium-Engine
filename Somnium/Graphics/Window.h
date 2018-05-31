#pragma once

#include <glew.h>
#include <glfw3.h>

namespace Somnium {
	namespace Graphics {
		extern void keyCallback(GLFWwindow*, int, int, int, int);
		extern void mouseButtonCallback(GLFWwindow*, int, int, int);
		extern void cursorPositionCallback(GLFWwindow*, double, double);
		class Window
		{
		public:
			Window(const char*, int, int);
			~Window();

			void clear(void)  const;
			void update(void) const;

			bool isClosed(void) const { return glfwWindowShouldClose(m_Window); }

			inline int getWidth(void) const { return m_Width; }
			inline int getHeight(void) const { return m_Height; }
			inline float getAspectRatio(void) const { return m_Width / (float)m_Height;  }

			bool isKeyPressed(unsigned int) const;
			bool isMouseButtonPressed(unsigned int) const;
			void getMousePosition(double& x, double& y) const;

			friend void resize(GLFWwindow*, int, int);

		private:
			void applySettings();
			bool init(void);

			friend void keyCallback(GLFWwindow*, int, int, int, int);
			friend void mouseButtonCallback(GLFWwindow*, int, int, int);
			friend void cursorPositionCallback(GLFWwindow*, double, double);

		private:
			friend struct GLFWwindow;

			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window = nullptr;

			bool m_Keys[GLFW_KEY_LAST] = { false };
			bool m_MouseButtons[GLFW_MOUSE_BUTTON_LAST] = { false };
			double m_MouseX = 0.0, m_MouseY = 0.0;
		};
	}
}
