#pragma once

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

namespace Somnium
{
	namespace Networking
	{
		class NetworkEntity
		{
		public:
			virtual ~NetworkEntity(){};

			virtual void broadcastMessage(std::string message) = 0;
			virtual void sendMessage(std::string address, std::string message) = 0;
			virtual void processMessage(std::string message) = 0;

		protected:
			NetworkEntity(){};
			int m_SocketID = 0;
			struct sockaddr_in m_Address;
		};
	}
}
