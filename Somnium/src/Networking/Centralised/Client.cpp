#include "Client.h"

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
			bool Client::connectToServer(sockaddr_in serverAddress)
			{
				return connect(m_SocketID, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0;
			}
		}
	}
}
