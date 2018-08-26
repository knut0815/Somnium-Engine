#pragma once

#ifdef WEB_BUILD
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <glew.h>
#endif


namespace Somnium
{
	namespace Utilities
	{
		namespace FrameRate
		{
			double startTime = 0;
			unsigned int fps;
			float timePerFrame;
			char fpsUI[128];

			void startFrameCounting() { startTime = glfwGetTime(); }

			void pauseDrawing(const unsigned int& elapsed, const unsigned int& frameRateLimit)
			{
				double  sleep = ((1000000.0 / frameRateLimit) - elapsed) / 1000000.0,
						start = glfwGetTime();

				while ((glfwGetTime() - start) < sleep);
			}

			void calculateFPS(unsigned int &frameRate, float &timePerFrame)
			{
				static double lastTime = glfwGetTime();
				static int nbFrames = 0;

				nbFrames++;

				if (glfwGetTime() - lastTime >= 1.0) {
					frameRate = nbFrames;
					timePerFrame = 1000.0 / double(nbFrames);

					nbFrames = 0;
					lastTime += 1.0;
				}
			}

			void limitFrameRate(const unsigned int& frameRateLimit)
			{
				if(frameRateLimit > 0)
					pauseDrawing(glfwGetTime() - startTime, frameRateLimit);
			}

			void update()
			{
				calculateFPS(fps, timePerFrame);
			}

			unsigned int& getFPS() { return fps; }
			float& getTimePerFrame() { return timePerFrame; }
		}
	}
}
