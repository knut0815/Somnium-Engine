#pragma once
#include "../Maths/Maths.h"

namespace Somnium
{
	namespace Graphics
	{
		class Vertex
		{
		/* METHODS & FUNCTIONS */
		public:
			Vertex(Maths::Vector3 position);
			~Vertex();

		/* VARIABLES */
		private:
			Maths::Vector3 m_Position;
			
		};
	}
}
