#pragma once

#include "Renderer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/VertexArray.h"

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
			~BatchRenderer();

			void beginMapping();
			virtual void submitToQueue(RenderableObject* object);
			void endMapping();
			virtual void flushQueue();

		private:
			void init();

		private:
			Buffers::VertexArray*  m_VAO;
			Buffers::VertexBuffer* m_VBO;
			Buffers::IndexBuffer* m_IBO;
			
			GLfloat* m_VertexDataBuffer;
			unsigned int m_CurrentVertexCount = 0;
			unsigned int m_CurrentIndex;
		};
	}
}