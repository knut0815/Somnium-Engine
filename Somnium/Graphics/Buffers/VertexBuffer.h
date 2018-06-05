#pragma once
#include <glew.h>
#include <vector>
#include "BufferStructure.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class VertexBuffer
			{
			public:
				VertexBuffer(GLfloat* data, size_t count, GLuint componentCount);
				VertexBuffer(std::vector<GLfloat>* data, size_t count, GLuint componentCount) { VertexBuffer(data->data(), count, componentCount); };
				VertexBuffer(std::vector<GLfloat>* data, GLuint componentCount) { VertexBuffer(data->data(), data->size(), componentCount); };
				~VertexBuffer();

				inline GLuint getComponentCount() const { return m_ComponentCount; }
				inline void bind() const;
				inline void unbind() const;

			private:
				GLuint m_BufferID;
				GLuint m_ComponentCount;
				BufferStructure m_BufferStructure;
			};
		}
	}
}