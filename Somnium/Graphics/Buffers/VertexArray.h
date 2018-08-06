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

				void draw(unsigned int count) const;

				inline void bind() const { glBindVertexArray(m_ArrayID); }
				inline void unbind() const { glBindVertexArray(0); }
	
			private:
				GLuint m_ArrayID;
				vector<VertexBuffer*> m_Buffers;
			};
		}
	}
}
