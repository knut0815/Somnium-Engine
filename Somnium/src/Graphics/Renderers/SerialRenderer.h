#pragma once
#include <vector>
#include <queue>
#include "../RenderableObject.h"
#include "../Camera.h"
#include "../Window.h"
#include "Renderer.h"
#include "../Buffers/FrameBuffer.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			class SerialRenderer
				: virtual public Renderer
			{
				/* Methods */
			public:
				SerialRenderer(const Window& window, Camera& camera)
					: Renderer(window, camera) {};
				virtual void submitToQueue(RenderableObject* object) { m_RenderQueue.push(object); }
				virtual void flushQueue();

			private:
				std::queue<RenderableObject*> m_RenderQueue;
				Shader blurShader = Shader("Resources/Graphics/Shaders/GL/Basic/passthrough.vert", "Resources/Graphics/Shaders/GL/Post-Processing/gaussianBlur.frag");
				Buffers::FrameBuffer m_FrameBuffer = Buffers::FrameBuffer(2);
			};
		}
	}
}
