#pragma once

#include "../NetworkEntity.h"
#include <vector>

namespace Somnium
{
	namespace Networking
	{
		namespace Decentralised
		{
			class Peer
			: public NetworkEntity
			{

			private:
				std::vector<Peer> m_Peers;
			};
		}
	}
}
