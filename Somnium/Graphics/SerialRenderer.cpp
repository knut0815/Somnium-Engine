#include "SerialRenderer.h"

namespace Somnium
{
	namespace Graphics
	{
		void SerialRenderer::updateCamera()
		{
			if (m_Window.isKeyPressed(GLFW_KEY_LEFT) || m_Window.isKeyPressed(GLFW_KEY_A))
				m_Camera.move(Maths::Vector3(-0.01f, 0, 0));
			if (m_Window.isKeyPressed(GLFW_KEY_RIGHT) || m_Window.isKeyPressed(GLFW_KEY_D))
				m_Camera.move(Maths::Vector3(0.01f, 0, 0));
			if (m_Window.isKeyPressed(GLFW_KEY_UP) || m_Window.isKeyPressed(GLFW_KEY_W))
			{
				if (m_Window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || m_Window.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
					m_Camera.move(Maths::Vector3(0, 0.01f, 0));
				else
					m_Camera.move(Maths::Vector3(0, 0, -0.01f));
			}
			if (m_Window.isKeyPressed(GLFW_KEY_DOWN) || m_Window.isKeyPressed(GLFW_KEY_S))
			{
				if (m_Window.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || m_Window.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
					m_Camera.move(Maths::Vector3(0, -0.01f, 0));
				else
					m_Camera.move(Maths::Vector3(0, 0, 0.01f));
			}
		}

		void SerialRenderer::flushQueue()
		{
			while (!m_RenderQueue.empty()) {
				RenderableObject* object = m_RenderQueue.front();
				m_RenderQueue.pop();

				const std::vector<Mesh*> meshes = object->getMeshes();

				for (Mesh* mesh : meshes)
				{
					mesh->bind();
					
					mesh->getShader().enable();
					
					mesh->getShader().setMatrix4("projectionMatrix", m_Camera.getProjection());
					mesh->getShader().setMatrix4("viewMatrix", m_Camera.getView());
					mesh->getShader().setMatrix4("modelMatrix", mesh->getModelMatrix());

					glDrawElements(GL_LINE_LOOP, (GLsizei)mesh->getIBOSize(), GL_UNSIGNED_SHORT, nullptr);
					
					mesh->getShader().disable();
					mesh->unbind();
				}
			}
		}
	}
}