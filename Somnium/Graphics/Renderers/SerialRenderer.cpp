#include "SerialRenderer.h"
#include "../../Maths/Maths.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Renderers
		{
			void SerialRenderer::flushQueue()
			{
				//m_FrameBuffers[0].bind();

				while (!m_RenderQueue.empty()) {
					RenderableObject* object = m_RenderQueue.front();
					m_RenderQueue.pop();

					const Mesh* mesh = object->getMesh();

					mesh->getShader().enable();

					mesh->getShader().setMatrix4("projectionMatrix", m_Camera.getProjection());
					mesh->getShader().setMatrix4("viewMatrix", m_Camera.getView());
					mesh->getShader().setMatrix4("modelMatrix", mesh->getModelMatrix());
					mesh->getShader().setVector3("camPos", m_Camera.getPosition());

					mesh->getVAO()->bind();
					mesh->getIBO()->bind();

					mesh->getVAO()->draw(mesh->getIBO()->getCount());

					mesh->getIBO()->unbind();
					mesh->getVAO()->unbind();
				}

				//m_FrameBuffers[0].unbind();
				//m_FrameBuffers[0].draw();

				m_Camera.drawUI();
			}
		}
	}
}
