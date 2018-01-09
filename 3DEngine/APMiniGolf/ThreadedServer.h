#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

//Includes
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <sstream>
#include <mutex>
#include "ThreadPool.h"
#include <vector>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define MAX_NUM_CLIENTS 2

class Server 
{
public:
	//Constructor
	Server(int, int);
	void Connect();		//Connect to server
	void Interact();	//Interact with the server
	void Terminate();	//Close the server

private:
	WSADATA m_WsaData;
	int m_iResult;

	struct addrinfo *m_Result = NULL;
	struct addrinfo m_Hints;

	int m_iSendResult;
	char m_RecvBuf[DEFAULT_BUFLEN];
	int m_RecvBufLen = DEFAULT_BUFLEN;

	int m_PortNum;
	int m_ClientID;
};

//Start the server thread helper function
namespace ServerThread
{
	int CreateServerThread(const std::string& Port);
};