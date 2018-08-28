#pragma once

#include "../NetworkEntity.h"
#include "Client.h"
#include <vector>
#include <thread>

#define SERVER_PORT 20080
#define MAXIMUM_CONNECTIONS 100

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
				Server() ;
				virtual ~Server();

				void run();

				void broadcastMessage(std::string message);
				void sendMessage(std::string address, std::string message);
				void processMessage(std::string message);

			private:
				void listenForClients();

			private:
				std::vector<Client> m_Clients;

				bool m_Running = false;
				std::thread m_ServerThread;
				struct sockaddr_in m_Address;
			};
		}
	}
}
