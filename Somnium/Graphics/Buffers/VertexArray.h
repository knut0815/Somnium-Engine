#pragma once

#include <vector>
#include <glew.h>

#include "VertexBuffer.h"

using namespace std;

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class VertexArray
			{
			public:
				VertexArray();
				~VertexArray();
	
				void addBuffer(VertexBuffer* vertexBuffer, GLuint index);

				inline void bind() const;
				inline void unbind() const;
	
			private:
				GLuint m_ArrayID;
				vector<VertexBuffer*> m_Buffers;
			};
		}
	}
}