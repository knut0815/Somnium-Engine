#pragma once

#include "Mesh.h"
#include <vector>

namespace Somnium
{
	namespace Graphics
	{
		class RenderableObject
		{
		/* Methods */
		public:
			RenderableObject() = default;
			RenderableObject(Mesh* mesh, const Maths::Vector3 &position = Maths::Vector3(0,0,0), const Maths::Vector3 &scale = Maths::Vector3(1, 1, 1), const Maths::Vector3 &orientation = Maths::Vector3(0, 0, 0))
				: m_Mesh(mesh), m_Position(position), m_Scale(scale), m_Orientation(orientation){};

			~RenderableObject() {};

			std::shared_ptr<Mesh> getMesh() { return m_Mesh; }

			inline const Maths::Vector3 getPosition() const { return m_Position;}

			void update();

		private:
			std::shared_ptr<Mesh> m_Mesh;
			Maths::Vector3 m_Position;
			Maths::Vector3 m_Scale;
			Maths::Vector3 m_Orientation;
		};
	}
}
