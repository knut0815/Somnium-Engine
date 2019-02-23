#include "Server.h"

#include <iostream>

#ifdef _WIN32

#else
	#include <arpa/inet.h>
#endif

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{

			Server::Server()
			{
#ifdef _WIN32

#else
				if(!(m_SocketID = socket(AF_INET, SOCK_STREAM, 0)))
				{
						printError(NetworkError::CREATE_SOCKET_FAIL);
						return;
				}

				m_Address.sin_family = AF_INET;
				m_Address.sin_addr.s_addr = INADDR_ANY;
				m_Address.sin_port = htons( SERVER_PORT );

				if(bind(m_SocketID, (struct sockaddr *) &m_Address, sizeof(m_Address)) < 0)
				{
						printError(NetworkError::BIND_SOCKET_FAIL);
						return;
				}
#endif
			}

			Server::~Server()
			{

				m_Running = false;
			}

			void Server::run()
			{
				if(m_Running) return;

				m_ServerThread = std::thread(&Server::listenForClients, this);
			}

			void Server::listenForClients()
			{
#ifdef _WIN32

#else
				m_Running = true;

				std::cout << "Server is listening for connections on " << inet_ntoa(m_Address.sin_addr) << ":" << htons(m_Address.sin_port) << std::endl;

				while(m_Running)
				{
					if(listen(m_SocketID, MAXIMUM_CONNECTIONS) < 0)
					{
						NetworkEntity::printError(NetworkError::SERVER_LISTEN_FAIL);
						return;
					}

					accept(m_SocketID, NULL, NULL);

					std::cout << "Connected to client" << std::endl;
				}
#endif
			}

			void Server::broadcastMessage(std::string message)
			{

			}

			void Server::sendMessage(std::string address, std::string message)
			{

			}

			void Server::processMessage(std::string message)
			{

			}
		}
	}
}
