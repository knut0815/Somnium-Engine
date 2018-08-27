#pragma once

#include <string>

namespace Somnium
{
	namespace Networking
	{
		class NetworkEntity
		{
public:
			void broadcastMessage(std::string message);
			void sendMessage(std::string address, std::string message);
			void processMessage(std::string message);
		};
	}
}
