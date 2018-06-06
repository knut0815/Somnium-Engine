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
				VertexBuffer(GLfloat* data, size_t count, GLuint componentCount, GLuint drawMode = GL_STATIC_DRAW);
				VertexBuffer(std::vector<GLfloat> data, size_t count, GLuint componentCount, GLuint drawMode = GL_STATIC_DRAW)
					: VertexBuffer(data.data(), count, componentCount, drawMode) {};
				VertexBuffer(std::vector<GLfloat> data, GLuint componentCount, GLuint drawMode = GL_STATIC_DRAW)
					: VertexBuffer(data.data(), data.size(), componentCount, drawMode) {};
				~VertexBuffer();

				inline GLuint getComponentCount() const { return m_ComponentCount; }
				inline void bind() const;
				inline void unbind() const;

			private:
				GLuint m_BufferID;
				const GLuint m_DrawMode;
				GLuint m_ComponentCount;
				BufferStructure m_BufferStructure;
			};
		}
	}
}