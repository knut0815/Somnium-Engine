#pragma once

#include <vector>
#include <string>

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
				unsigned int m_BufferSize = 0;
				std::vector<BufferItem> m_Structure;
			};
		}
	}
}
