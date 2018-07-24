#include "Window.h"
#include <iostream>

using namespace std;

#define ENABLE_DEBUG_MODE false

namespace Somnium
{
	namespace Graphics
	{
		void resize(GLFWwindow*, int, int);
		void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

		Window::Window(const char* title, int width, int height)
			:m_Title(title), m_Width(width), m_Height(height)
		{
			if (!init())
				glfwTerminate();
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::applySettings()
		{
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, resize);
			glfwSetKeyCallback(m_Window, keyCallback);
			glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
			glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
			glfwSetScrollCallback(m_Window, mouseScrollCallback);

			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Allows for infinite cursor movement; necessary for camera rotation

			glfwSwapInterval(0);

			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_FRAMEBUFFER_SRGB);
		}

		bool Window::init()
		{
			cout << "------------INITIALISING GRAPHICS------------" << endl;
			cout << " GLFW\t\t";

			if (!glfwInit())
			{
				cerr << "GLFW initialisation error" << endl;
				return false;
			}

			cout << glfwGetVersionString() << endl;

			glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
			glfwWindowHint(GLFW_SAMPLES, 4);

			#ifdef __APPLE__
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			cout << " OpenGL\t\t";

			if (!m_Window)
			{
				cerr << "Failed to create GL Window" << endl;
				glfwTerminate();
				return false;
			}

			applySettings();

			cout << glGetString(GL_VERSION) << endl;
			cout << " GLSL\t\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
			cout << " GPU\t\t" << glGetString(GL_RENDERER) << endl;

			cout << " GLEW\t\t";

			glewExperimental = GL_TRUE;

			if (glewInit() != GLEW_OK) //Must be after the ContextCurrent call
			{
				cerr << "GLEW initialisation failed";
				return false;
			}

			cout << glewGetString(GLEW_VERSION) << endl;

			cout << " FreeType\t";
			if (FT_Init_FreeType(&m_FreeType))
			{
				std::cerr << "Could not initialise FreeType" << std::endl;
				return false;
			}

			int ftMaj, ftMin, ftPatch;
			FT_Library_Version(m_FreeType, &ftMaj, &ftMin, &ftPatch);

			std::cout << ftMaj << "." << ftMin << " Patch " << ftPatch << endl;

			/* DEBUG MODE */

			if (ENABLE_DEBUG_MODE)
			{
				glEnable(GL_DEBUG_OUTPUT);
				glDebugMessageCallback(errorCallback, 0);

#ifndef _WIN32
				printf("\33[31m");
#endif
				printf("!-- DEBUG MODE ENABLED --!\r\n", 0x1B, 31);
#ifndef _WIN32
				printf("\33[37m");
#endif
			}
			cout << "---------------------------------------------" << endl << endl;

			return true;
		}

		bool Window::isKeyPressed(unsigned int keyCode) const
		{
			if (keyCode >= GLFW_KEY_LAST)
				return false;

			return m_Keys[keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int buttonCode) const
		{
			if (buttonCode >= GLFW_MOUSE_BUTTON_LAST)
				return false;

			return m_MouseButtons[buttonCode];
		}

		void Window::getMousePosition(int& x, int& y) const
		{
			x = m_MouseX;
			y = m_MouseY;
		}

		void Window::getMouseScroll(int& xOffset, int& yOffset) const
		{
			xOffset = m_MouseScrollXOffset;
			yOffset = m_MouseScrollYOffset;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() const
		{
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		void resize(GLFWwindow* window, int width, int height)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_Width = width;
			currentWindow->m_Height = height;

			glViewport(0, 0, width, height);
		}

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursorPositionCallback(GLFWwindow* window, double mX, double mY)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_MouseX = mX;
			currentWindow->m_MouseY = mY;
		}

		void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
		{
			Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);

			currentWindow->m_MouseScrollXOffset += xOffset;
			currentWindow->m_MouseScrollYOffset += yOffset;

		}

		void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
		{


#ifndef _WIN32
		static const char* errorFlag = "\33[31m** GL ERROR **\33[37m";
#else
        static const char* errorFlag = "** GL ERROR **";
#endif
			fprintf(stderr, "\r\nGL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\r\n",
				(type == GL_DEBUG_TYPE_ERROR ? errorFlag : ""),
				type, severity, message);

			if(type == GL_DEBUG_TYPE_ERROR)
				cin.get();


		}
	}
}
