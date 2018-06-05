#include "SerialRenderer.h"

namespace Somnium
{
	namespace Graphics
	{
		void SerialRenderer::flushQueue()
		{
			while (!m_RenderQueue.empty()) {
				RenderableObject* object = m_RenderQueue.front();
				m_RenderQueue.pop();

				const std::vector<Mesh*> meshes = object->getMeshes();

				for (Mesh* mesh : meshes)
				{
					mesh->getShader().enable();
					
					mesh->getShader().setMatrix4("projectionMatrix", m_Camera.getProjection());
					mesh->getShader().setMatrix4("viewMatrix", m_Camera.getView());
					mesh->getShader().setMatrix4("modelMatrix", mesh->getModelMatrix());

					mesh->getVAO()->bind();
					mesh->getIBO()->bind();
					glDrawElements(GL_LINE_LOOP, (GLsizei)mesh->getIBOSize(), GL_UNSIGNED_SHORT, nullptr);
					mesh->getIBO()->unbind();
					mesh->getVAO()->unbind();

					mesh->getShader().disable();
				}
			}
		}
	}
}