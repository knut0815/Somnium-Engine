#pragma once

#include <vector>
#include <string>

#define SHADER_POSITION_INDEX 0
#define SHADER_NORMAL_INDEX 1
#define SHADER_TEXTURE_COORDINATE_INDEX 2

namespace Somnium
{
	namespace Graphics
	{
		namespace Buffers
		{
			struct BufferItem
			{
				std::string name;

			};

			class BufferStructure
			{
			public:
				BufferStructure() {};
				~BufferStructure() {};

			private:
				unsigned int m_BufferSize;
				std::vector<BufferItem> m_Structure;
			};
		}
	}
}
