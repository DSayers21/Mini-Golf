#include "ThreadedClient.h"

void ThreadedClient::start(const char* ipaddress, const char* port) 
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ipaddress, port, &hints, &result);
	if (iResult != 0) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) 
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) 
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return;
	}

	printf("Connected!\n");
}

void ThreadedClient::sendthis(const char* buffer) 
{
	iResult = send(ConnectSocket, buffer, sizeof(buffer), 0);
	if (iResult == SOCKET_ERROR) 
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		terminate();
		return;
	}
}

const std::string& ThreadedClient::getthis() 
{
	//iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	return lastrecvbuf;
}

void ThreadedClient::sendmsg() 
{
	while (true) 
	{
		printf("Client: ");
		fgets(recvbuf, 255, stdin);
		iResult = send(ConnectSocket, recvbuf, sizeof(recvbuf), 0);
		if (iResult == SOCKET_ERROR) 
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			terminate();
			return;
		}
	}
}

void ThreadedClient::getmsg() 
{
	while (true) 
	{
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("Server says: %s\n", recvbuf);
			lastrecvbuf = recvbuf;
		}
	}
}

void ThreadedClient::interact() 
{
	std::thread t(&ThreadedClient::getmsg, this);
	//sendmsg();
	t.detach();
}

void ThreadedClient::terminate() 
{
	closesocket(ConnectSocket);
	WSACleanup();
}