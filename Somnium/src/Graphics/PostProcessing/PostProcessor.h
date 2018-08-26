#pragma once

#ifdef WEB_BUILD
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <glew.h>
#endif

#include <queue>
#include "../Shaders/Shader.h"
#include "PostProcessingUnit.h"
#include "../Mesh.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			class PostProcessor
			{
				public:
					static void initialise();

					PostProcessor();
					virtual ~PostProcessor();

					static void drawScreen(Shaders::Shader* shader = s_ScreenShader);
					static inline void submitToQueue(PostProcessingUnit*  ppu) { PostProcessor::m_PostProcessingUnits.push(ppu); }
					static void process(Buffers::FrameBuffer* fbo);
				private:

					static void start() { glDisable(GL_DEPTH_TEST); };

					static void end() { glEnable(GL_DEPTH_TEST); }

				private:
					static std::queue<PostProcessingUnit*> m_PostProcessingUnits;

					static Shaders::Shader* s_ScreenShader;
					static Buffers::VertexArray* s_ScreenVAO;
					static Buffers::IndexBuffer* s_ScreenIBO;
					static bool s_Initialised;
			};
		}
	}
}
