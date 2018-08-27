#pragma once

#include "../NetworkEntity.h"
#include <string>

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
			class Client
			: public NetworkEntity
			{
			public:
				Client();
				virtual ~Client();

				void broadcastMessage(std::string message);
				void sendMessage(std::string address, std::string message);
				void processMessage(std::string message);

				bool connect();
				void disconnect();

			private:
				//Server m_ServerAddr;
			};
		}
	}
}
