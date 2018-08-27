#pragma once

#include "../NetworkEntity.h"
#include "Client.h"
#include <vector>

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
			class Server
			: public NetworkEntity
			{
			public:
				void start();
				void listen();
				void accept();

				void broadcastMessage(std::string message);
				void sendMessage(std::string address, std::string message);
				void processMessage(std::string message);
			private:
				std::vector<Client> m_Clients;
			};
		}
	}
}
