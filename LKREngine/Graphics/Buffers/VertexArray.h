#pragma once

#include <vector>
#include <glew.h>

#include "Buffer.h"

using namespace std;

namespace LKREngine
{
	namespace Graphics
	{
		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer*, GLuint);

			inline void Bind() const;
			inline void Unbind() const;

		private:
			GLuint m_ArrayID;
			vector<Buffer*> m_Buffers;
		};
	}
}