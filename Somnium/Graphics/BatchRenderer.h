#pragma once

#include "Renderer.h"

namespace Somnium
{
	namespace Graphics
	{
		class BatchRenderer : virtual Renderer
		{
		public:
			BatchRenderer(const Window& window, Camera camera)
				: Renderer(window, camera) 
			{
				init();
			};
			
			virtual void flushQueue();
			virtual void submitToQueue(RenderableObject* object);
			virtual void updateCamera();

		private:
			void init();

		private:
			GLuint m_VAO, m_VBO, m_IBO;
			std::vector<GLushort> m_Indices;
		};
	}
}