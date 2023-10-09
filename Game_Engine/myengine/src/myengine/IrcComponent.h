#include "Component.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <vector>

namespace myengine
{
	struct IrcComponent : Component
	{
		IrcComponent(); //Initialize Winsock, connect
		~IrcComponent(); // Close socket

		void onTick();//Read data into incoming buffer, process
					  //Write data from outgoing buffer

		void authenticate(); // Add NICK and USER messages to outgoing
		bool disconnected(); //A 0 recv can set this flag

	private:
		SOCKET m_socket;
		std::vector<unsigned char> m_incoming;
		std::vector<unsigned char> m_outgoing;

		bool m_authenticated;
		bool m_disconnected;
	};
}