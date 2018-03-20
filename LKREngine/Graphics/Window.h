#pragma once

#include <glew.h>
#include <glfw3.h>

namespace LKREngine {
	namespace Graphics {
		class Window
		{
		public:
			Window(const char*, int, int);
			~Window();

			void Clear(void)  const;
			void Update(void) const;

			bool IsClosed(void) const { return glfwWindowShouldClose(m_Window); }
			
			inline const int GetWidth(void) const { return m_Width; }
			inline const int GetHeight(void) const { return m_Height; }

			bool IsKeyPressed(unsigned int) const;
			bool IsMouseButtonPressed(unsigned int) const;
			void GetMousePosition(double& x, double& y) const;

			friend void Resize(GLFWwindow*, int, int);

		private:
			void ApplySettings();
			bool Init(void);
			friend static void KeyCallback(GLFWwindow*, int, int, int, int);
			friend static void MouseButtonCallback(GLFWwindow*, int, int, int);
			friend static void CursorPositionCallback(GLFWwindow*, double, double);

		private:
			friend struct GLFWwindow;

			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;

			bool m_Keys[GLFW_KEY_LAST] = { false };
			bool m_MouseButtons[GLFW_MOUSE_BUTTON_LAST] = { false };
			double m_MouseX = 0.0, m_MouseY = 0.0;
		};
	}
}