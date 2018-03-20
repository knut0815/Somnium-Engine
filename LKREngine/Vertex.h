#pragma once
#include "Maths\Maths.h"

namespace LKREngine
{
	namespace Graphics
	{
		class Vertex
		{
		public:
			Vertex(Maths::Vector3 position);
			~Vertex();

		private:
			Maths::Vector3 m_Position;
			
		};
	}
}