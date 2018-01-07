#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

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

class Server {
	WSADATA wsaData;
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	int portnum;
	int clientid;

public:
	Server(int, int);
	void connect();
	void interact();
	void terminate();
};

namespace ServerThread
{
	int CreateServerThread(const std::string& Port);
};