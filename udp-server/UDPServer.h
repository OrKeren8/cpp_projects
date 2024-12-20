#pragma once
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <time.h>

#define TIME_PORT	27015

class UDPServer
{
private:
	static const int SEND_BUFFER_SIZE = 255;
	static const int RECEIVE_BUFFER_SIZE = 2;

	WSAData m_wsaData;
	SOCKET m_socket;
	sockaddr_in m_serverService;
	sockaddr m_clientAddr;
	int m_clientAddrLen;
	int m_bytesSent = 0;
	int m_bytesRecv = 0;
	char m_sendBuff[SEND_BUFFER_SIZE];
	char m_recvBuff[RECEIVE_BUFFER_SIZE];

	bool closeConnectionAfterException(int i_status);
	static void getFullTime(char o_buffer[]);

public:
	void InitServer();
	void CloseConnection();
	void ServerRun();
};
