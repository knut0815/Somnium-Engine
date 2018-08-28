#pragma once

#include "../NetworkEntity.h"
#include <string>

#define CLIENT_PORT 20080

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
				Client() { }
				virtual ~Client();

				void broadcastMessage(std::string message);
				void sendMessage(std::string address, std::string message);
				void processMessage(std::string message);

				bool connectToServer(struct sockaddr_in serverAddress);
				void disconnect();

			private:
				//Server m_ServerAddr;
			};
		}
	}
}
