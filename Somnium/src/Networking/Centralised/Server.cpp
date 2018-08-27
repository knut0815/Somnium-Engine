#include "Server.h"

#include <cerrno>
#include <iostream>
#include <string.h>

#define PORT 20080
#define MAXIMUM_CONNECTIONS 100

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
			Server::Server()
			{
				if(!(m_SocketID = socket(AF_INET, SOCK_STREAM, 0)))
				{
					printError(NetworkError::CREATE_SOCKET_FAIL);
					return;
				}

				m_Address.sin_family = AF_INET;
				m_Address.sin_addr.s_addr = INADDR_ANY;
				m_Address.sin_port = htons( PORT );

				if(bind(m_SocketID, (struct sockaddr *) &m_Address, sizeof(m_Address)) < 0)
				{
					printError(NetworkError::BIND_SOCKET_FAIL);
					return;
				}
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
				m_Running = true;

				std::cout << "Server is listening for connections..." << std::endl;

				while(m_Running)
				{
					if(listen(m_SocketID, MAXIMUM_CONNECTIONS) < 0)
					{
						printError(NetworkError::SERVER_LISTEN_FAIL);
						return;
					}
				}
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

			void Server::printError(NetworkError errorCode)
			{
				switch(errorCode)
				{
				case NetworkError::CREATE_SOCKET_FAIL:
					std::cerr << "Socket creation failed on SERVER: ";
					break;
				case NetworkError::BIND_SOCKET_FAIL:
					std::cerr << "Socket binding failed on SERVER: ";
					break;
				case NetworkError::SERVER_LISTEN_FAIL:
					std::cerr << "Failed to set the socket mode to listen on SERVER: ";
					break;
				default:
					std::cerr << "Error on SERVER: ";
					break;
				}

				std::cerr << strerror(errno) << std::endl;
			}
		}
	}
}
