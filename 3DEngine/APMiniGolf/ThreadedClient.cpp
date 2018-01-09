//Includes
#include "ThreadedClient.h"

void ThreadedClient::Start(const char* ipaddress, const char* port) 
{
	// Initialize Winsock
	m_iResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
	if (m_iResult != 0)
	{
		//Display error message
		printf("WSAStartup failed with error: %d\n", m_iResult);
		return;
	}

	//Prepare hints
	ZeroMemory(&m_Hints, sizeof(m_Hints));
	m_Hints.ai_family = AF_UNSPEC;
	m_Hints.ai_socktype = SOCK_STREAM;
	m_Hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	m_iResult = getaddrinfo(ipaddress, port, &m_Hints, &m_Result);
	if (m_iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", m_iResult);
		WSACleanup();
		return;
	}

	// Attempt to connect to an address until one succeeds
	for (m_Ptr = m_Result; m_Ptr != NULL; m_Ptr = m_Ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		m_ConnectSocket = socket(m_Ptr->ai_family, m_Ptr->ai_socktype, m_Ptr->ai_protocol);
		if (m_ConnectSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return;
		}

		// Connect to server.
		m_iResult = connect(m_ConnectSocket, m_Ptr->ai_addr, (int)m_Ptr->ai_addrlen);
		if (m_iResult == SOCKET_ERROR)
		{
			closesocket(m_ConnectSocket);
			m_ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}
	//Free the info
	freeaddrinfo(m_Result);
	//Test if the socket is invalid
	if (m_ConnectSocket == INVALID_SOCKET) 
	{
		//Display message
		printf("Unable to connect to server!\n");
		//Clean
		WSACleanup();
		return;
	}
	//Display message
	printf("Connected!\n");
}

void ThreadedClient::SendThis(const char* buffer) 
{
	//Send message
	m_iResult = send(m_ConnectSocket, buffer, sizeof(buffer), 0);
	//Check if socket is bad
	if (m_iResult == SOCKET_ERROR)
	{
		//Display message
		printf("send failed with error: %d\n", WSAGetLastError());
		//Terminate
		terminate();
		return;
	}
}

void ThreadedClient::SendMsg() 
{
	//While active, get message from the server
	while (true) 
	{
		printf("Client: ");
		//Send message
		fgets(m_Recvbuf, 255, stdin);
		m_iResult = send(m_ConnectSocket, m_Recvbuf, sizeof(m_Recvbuf), 0);
		//Check if socket is bad
		if (m_iResult == SOCKET_ERROR)
		{
			//Display message
			printf("send failed with error: %d\n", WSAGetLastError());
			//Terminate
			terminate();
			return;
		}
	}
}

void ThreadedClient::GetMsg() 
{
	//While active, get message from the server
	while (true) 
	{
		//Get the message
		m_iResult = recv(m_ConnectSocket, m_Recvbuf, m_RecvBufLen, 0);
		if (m_iResult > 0) //Test if the message is valid
		{
			//Display the received message
			printf("Server says: %s\n", m_Recvbuf);
			m_LastRecvBuf = m_Recvbuf;
		}
	}
}

void ThreadedClient::Interact() 
{
	//Start thread which runs get message constantly
	std::thread t(&ThreadedClient::GetMsg, this);
	//Remove thread
	t.detach();
}

void ThreadedClient::Terminate() 
{
	//Close socket
	closesocket(m_ConnectSocket);
	WSACleanup();
}