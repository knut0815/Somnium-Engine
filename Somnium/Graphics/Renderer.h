#pragma once
#include <vector>
#include "RenderableObject.h"
#include "Camera.h"

namespace Somnium
{
	namespace Graphics
	{
		class Renderer 
		{
		/* Methods */
		public:
			Renderer() = default;
			Renderer(std::vector<RenderableObject> objects) : m_Objects(objects) {};
			~Renderer() {};

			void addObjectToScene(RenderableObject object) { m_Objects.push_back(object); };

		private:
			
		/* Variables */
		public:

		private:
			std::vector<RenderableObject> m_Objects;
			std::vector<Camera> m_Cameras;
		};
	}
}