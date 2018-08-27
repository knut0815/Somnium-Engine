#pragma once

#include "../NetworkEntity.h"
#include "Client.h"
#include <vector>
#include <thread>

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
			enum NetworkError { CREATE_SOCKET_FAIL, BIND_SOCKET_FAIL, SERVER_LISTEN_FAIL };

			class Server
			: public NetworkEntity
			{
			public:
				Server();
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

				void printError(NetworkError errorCode);
			};
		}
	}
}
