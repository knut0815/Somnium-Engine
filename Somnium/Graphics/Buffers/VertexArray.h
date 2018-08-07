#pragma once

#include <vector>
#ifdef WEB_BUILD 
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else 
	#include <glew.h> 
#endif

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
