#pragma once

#include "../Maths/Vector3.h"
#include "../Graphics/RenderableObject.h"

namespace Somnium
{
	namespace DebugTools
	{
		class NavigationGrid : public Graphics::RenderableObject
		{
		public:
			NavigationGrid(float divisionSize, Maths::Vector3 gridSize)
				: m_DivisionSize(divisionSize), m_GridSize(gridSize) { };
			~NavigationGrid();

			void show() { m_Show = true; }
			void hide() { m_Show = false; }
			void toggle() { m_Show = !m_Show; }
			void draw();

		private:
			float m_DivisionSize;
			Maths::Vector3 m_GridSize;
			bool m_Show;
		};
	}
}