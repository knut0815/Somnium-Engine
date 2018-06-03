#pragma once

#include "Renderer.h"

namespace Somnium
{
	namespace Graphics
	{
		class BatchRenderer : virtual public Renderer
		{
		public:
			BatchRenderer(const Window& window, Camera camera)
				: Renderer(window, camera) 
			{
				init();
			};
			void beginMapping();
			virtual void submitToQueue(RenderableObject* object);
			void endMapping();
			virtual void flushQueue();

		private:
			void init();

		private:
			GLuint m_VAO, m_VBO, m_IBO;
			std::vector<GLushort> m_Indices;
			Vertex* m_VertexDataBuffer;
			unsigned int m_CurrentIndex;
		};
	}
}