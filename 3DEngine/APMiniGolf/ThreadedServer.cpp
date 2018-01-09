//Includes
#include "ThreadedServer.h"

//Info namespace to easily access information
namespace Info 
{
	std::mutex mtx;
	SOCKET ListenSocket[MAX_NUM_CLIENTS];
	SOCKET ClientSocket[MAX_NUM_CLIENTS];
}

Server::Server(int port, int i) 
{
	//Setup the server
	this->m_PortNum = port + i;
	this->m_ClientID = i;
}

void Server::Connect() 
{
	//Setup default sockets
	Info::ListenSocket[m_ClientID] = INVALID_SOCKET;
	Info::ClientSocket[m_ClientID] = INVALID_SOCKET;

	//Initialize Winsock
	m_iResult = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
	if (m_iResult != 0) //Check if init properly
	{
		//Display error message
		printf("WSAStartup failed with error: %d\n", m_iResult);
		return;
	}

	//Prepare hints
	ZeroMemory(&m_Hints, sizeof(m_Hints));
	m_Hints.ai_family = AF_INET;
	m_Hints.ai_socktype = SOCK_STREAM;
	m_Hints.ai_protocol = IPPROTO_TCP;
	m_Hints.ai_flags = AI_PASSIVE;

	//Resolve the server address and port
	std::string s = std::to_string(m_PortNum);
	const char* portstr = s.c_str();
	//Get the address info
	m_iResult = getaddrinfo(NULL, portstr, &m_Hints, &m_Result);
	if (m_iResult != 0) //Check if address info failed
	{
		//Display error message
		printf("getaddrinfo failed with error: %d\n", m_iResult);
		//Clean
		WSACleanup();
		return;
	}

	// Create a SOCKET for connecting to server
	Info::ListenSocket[m_ClientID] = socket(m_Result->ai_family, m_Result->ai_socktype, m_Result->ai_protocol);
	if (Info::ListenSocket[m_ClientID] == INVALID_SOCKET) //Check if invalud socket
	{
		//Display error message
		printf("socket failed with error: %ld\n", WSAGetLastError());
		//Free and clean
		freeaddrinfo(m_Result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket
	m_iResult = bind(Info::ListenSocket[m_ClientID], m_Result->ai_addr, (int)m_Result->ai_addrlen);
	if (m_iResult == SOCKET_ERROR) //Check for socket error
	{
		//Display error message
		printf("bind failed with error: %d\n", WSAGetLastError());
		//Free address, close socket and clean
		freeaddrinfo(m_Result);
		closesocket(Info::ListenSocket[m_ClientID]);
		WSACleanup();
		return;
	}
	//Free the address information
	freeaddrinfo(m_Result);

	//Listen to the socket
	m_iResult = listen(Info::ListenSocket[m_ClientID], SOMAXCONN);
	if (m_iResult == SOCKET_ERROR) //Check for socket error
	{
		//Display error message
		printf("listen failed with error: %d\n", WSAGetLastError());
		//Close socket and clean
		closesocket(Info::ListenSocket[m_ClientID]);
		WSACleanup();
		return;
	}

	// Accept a client socket
	Info::ClientSocket[m_ClientID] = accept(Info::ListenSocket[m_ClientID], NULL, NULL);
	if (Info::ClientSocket[m_ClientID] == INVALID_SOCKET) //Check if socket is invalid
	{
		//Display error message
		printf("accept failed with error: %d\n", WSAGetLastError());
		//Close socket and clean
		closesocket(Info::ListenSocket[m_ClientID]);
		WSACleanup();
		return;
	}
}

void Server::Interact() 
{
	//While active
	while (true) 
	{
		printf("listening\n"); //Display message
		//Receive message
		m_iResult = recv(Info::ClientSocket[m_ClientID], m_RecvBuf, m_RecvBufLen, 0);
		if (m_iResult > 0) //If message was received
		{
			//Display message
			printf("Client %d says: %s\n", m_PortNum, m_RecvBuf);
			//Lock
			Info::mtx.lock();
			printf("broadcasting\n");
			//Loop over all clients
			for (int i = 0; i < MAX_NUM_CLIENTS; i++) 
			{
				//If the client is the current client, then return
				if (m_ClientID == i) continue;
				//Send message
				m_iSendResult = send(Info::ClientSocket[i], m_RecvBuf, m_iResult, 0);
				//Check if there is a socket error
				if (m_iSendResult == SOCKET_ERROR) 
				{
					//Display message
					printf("send failed with error: %d\n", WSAGetLastError());
					//Terminate
					terminate();
					return;
				}
			}
			//Unlock
			Info::mtx.unlock();
		}
		else if (m_iResult == 0) //Check if equals 0
			printf("Connection closing...\n");
		else 
		{
			//Display error, and terminate
			printf("recv failed with error: %d\n", WSAGetLastError());
			terminate();
			return;
		}
	}
}

void Server::Terminate() 
{
	//Shutdown the connection since we're done
	m_iResult = shutdown(Info::ClientSocket[m_ClientID], SD_SEND);
	if (m_iResult == SOCKET_ERROR) //Check for socket error
	{
		//Display error message
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		//Close socket and clean up
		closesocket(Info::ClientSocket[m_ClientID]);
		WSACleanup();
		return;
	}
	//Close socket and clean up
	closesocket(Info::ClientSocket[m_ClientID]);
	WSACleanup();
}

int ServerThread::CreateServerThread(const std::string & Port)
{
	//List of Servers
	std::vector<Server> servers;
	//Create thread pool
	ThreadPool threads(MAX_NUM_CLIENTS);
	//Loop over all clients
	for (int i = 0; i < MAX_NUM_CLIENTS; i++)
	{
		//Get port
		int port = atoi(Port.c_str());
		//Add thread
		threads.enqueue([port, i]
		{
			printf("Starting client %d\n", (port + i));	//Display message
			Server server = Server(port, i);			//Create server port
			server.Connect();							//Connect
			server.Interact();							//Interact with server
		});
	}
	//Display message
	printf("LAUNCHED...\n");
	//Return
	return 0;
}