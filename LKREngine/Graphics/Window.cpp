#include "Window.h"
#include <iostream>

using namespace std;

namespace LKREngine 
{
	namespace Graphics 
	{
		void Resize(GLFWwindow*, int, int);

		Window::Window(const char* title, int width, int height)
			:m_Title(title), m_Width(width), m_Height(height)
		{
			if (!Init())
				glfwTerminate();
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::ApplySettings()
		{
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, Resize);
			glfwSetKeyCallback(m_Window, KeyCallback);
			glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
			glfwSetCursorPosCallback(m_Window, CursorPositionCallback);
			glfwSwapInterval(0);

			glFrontFace(GL_CW);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_FRAMEBUFFER_SRGB);
		}

		bool Window::Init()
		{
			cout << "-------INITIALISING GRAPHICS-------" << endl;
			cout << "GLFW\t";

			if (!glfwInit())
			{
				cerr << "GLFW initialisation error" << endl;
				return false;
			}

			cout << glfwGetVersionString() << endl;

			glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
			glfwWindowHint(GLFW_SAMPLES, 4);

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			cout << "OpenGL\t";

			if (!m_Window)
			{
				cerr << "Failed to create GL Window" << endl;
				glfwTerminate();
				return false;
			}

			ApplySettings();

			cout << glGetString(GL_VERSION) << endl;
			cout << "GLSL\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
			cout << "GPU\t" << glGetString(GL_RENDERER) << endl;

			cout << "GLEW\t";

			if (glewInit() != GLEW_OK) //Must be after the ContextCurrent call
			{
				cerr << "GLEW initialisation failed";
				return false;
			}

			cout << glewGetString(GLEW_VERSION) << endl;
			cout << "-----------------------------------" << endl << endl;

			return true;
		}

		bool Window::IsKeyPressed(unsigned int keyCode) const
		{
			if (keyCode >= GLFW_KEY_LAST)
				return false;

			return m_Keys[keyCode];
		}

		bool Window::IsMouseButtonPressed(unsigned int buttonCode) const
		{
			if (buttonCode >= GLFW_MOUSE_BUTTON_LAST)
				return false;

			return m_MouseButtons[buttonCode];
		}

		void Window::GetMousePosition(double& x, double& y) const
		{
			x = m_MouseX;
			y = m_MouseY;
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update() const
		{
			if (GLenum error = glGetError() != GL_NO_ERROR)
				cout << glewGetErrorString(error) << endl;

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		void Resize(GLFWwindow* window, int width, int height)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_Width = width;
			currentWindow->m_Height = height;

			glViewport(0, 0, width, height);
		}

		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_Keys[key] = action != GLFW_RELEASE;
		}

		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_MouseButtons[button] = action != GLFW_RELEASE;
		}


		void CursorPositionCallback(GLFWwindow* window, double mX, double mY)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_MouseX = mX;
			currentWindow->m_MouseY = mY;
		}
	}
}