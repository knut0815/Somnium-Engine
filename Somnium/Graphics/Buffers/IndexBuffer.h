#pragma once
#include <glew.h>
#include <vector>

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			class IndexBuffer
			{
			public:
				IndexBuffer(GLushort* indices, size_t numberOfIndices);
				IndexBuffer(std::vector<GLushort> data, size_t count) 
					: IndexBuffer(data.data(), count) {};
				IndexBuffer(std::vector<GLushort> data)
					: IndexBuffer(data.data(), data.size()) {};
				
				~IndexBuffer();

				inline GLuint getCount() const { return m_Count; }
				inline void bind() const;
				inline void unbind() const;

			private:
				GLuint m_BufferID;
				GLuint m_Count;
			};
		}
	}
}
