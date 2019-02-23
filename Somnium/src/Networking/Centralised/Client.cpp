#include "Client.h"

namespace Somnium
{
	namespace Networking
	{
		namespace Centralised
		{
#ifdef _WIN32
			bool Client::connectToServer()
			{
				return false;
			}
#else
			bool Client::connectToServer(sockaddr_in serverAddress)
			{
				return connect(m_SocketID, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0;
			}
#endif
		}
	}
}
