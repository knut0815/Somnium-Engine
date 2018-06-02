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
			RenderableObject(std::vector<Mesh*> meshes, const Maths::Vector3 &position = Maths::Vector3(0,0,0), const Maths::Vector3 &scale = Maths::Vector3(1, 1, 1), const Maths::Vector3 &orientation = Maths::Vector3(0, 0, 0))
				: m_Meshes(meshes), m_Position(position), m_Scale(scale), m_Orientation(orientation){};
			RenderableObject(Mesh* mesh) { m_Meshes.push_back(mesh);  };
			~RenderableObject() { for (Mesh* mesh : m_Meshes) delete mesh; };

			std::vector<Mesh*> getMeshes() { return m_Meshes; }

			inline const Maths::Vector3 getPosition() const { return m_Position;}

			void update();

		private:
			std::vector<Mesh*> m_Meshes;
			Maths::Vector3 m_Position;
			Maths::Vector3 m_Scale;
			Maths::Vector3 m_Orientation;
		};
	}
}
