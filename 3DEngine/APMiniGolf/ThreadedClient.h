#pragma once

#define WIN32_LEAN_AND_MEAN

//Includes
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512

class ThreadedClient 
{
public:
	//Start the server
	void Start(const char*, const char*);
	//Send a message to server
	void SendThis(const char* buffer);
	//Get the last message received
	inline const std::string& GetLstReceived() { return m_LastRecvBuf; }
	//Set the last message received
	inline void SetLstReceived(const std::string& Name) { m_LastRecvBuf = Name; }
	//Send a message
	void SendMsg();
	//Get the message from the server
	void GetMsg();
	//Interact with the server
	void Interact();
	//Destroy the server
	void Terminate();

private:
	WSADATA m_WsaData;
	//Client Socket
	SOCKET m_ConnectSocket = INVALID_SOCKET;
	//Information
	struct addrinfo *m_Result = NULL,
		*m_Ptr = NULL,
		m_Hints;
	//Sending buffer
	char *m_Sendbuf = "Test";
	//Receive buffer 
	char m_Recvbuf[DEFAULT_BUFLEN];
	//Last message received from the server
	std::string m_LastRecvBuf;

	int m_iResult;
	int m_RecvBufLen = DEFAULT_BUFLEN;
};