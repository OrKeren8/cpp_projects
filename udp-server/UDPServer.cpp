#define _CRT_SECURE_NO_WARNINGS
#include "UDPServer.h"
#include <string.h>


void UDPServer::InitServer() {

	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &m_wsaData))
	{
		cout << "Time Server: Error at WSAStartup()\n";
		return;
	}

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (INVALID_SOCKET == m_socket)
	{
		cout << "Time Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	m_serverService.sin_family = AF_INET;
	m_serverService.sin_addr.s_addr = INADDR_ANY;	//inet_addr("127.0.0.1");
	m_serverService.sin_port = htons(TIME_PORT);

	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&m_serverService, sizeof(m_serverService)))
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		CloseConnection();
		return;
	}

	m_clientAddrLen = sizeof(m_clientAddr);
	cout << "Time Server: Wait for clients' requests.\n";
}

void UDPServer::CloseConnection() {
	cout << "Time Server: Closing Connection.\n";
	closesocket(m_socket);
	WSACleanup();
}

bool UDPServer::closeConnectionAfterException(int i_status) {
	bool ifError = false;

	if (SOCKET_ERROR == i_status)
	{
		cout << "Time Server: " << WSAGetLastError() << endl;
		CloseConnection();
		ifError = true;
	}
	return ifError;
}

void UDPServer::ServerRun() {
	bool runServerLoop = true;
	while (runServerLoop)
	{
		m_bytesRecv = recvfrom(m_socket, m_recvBuff, 2, 0, &m_clientAddr, &m_clientAddrLen);
		if (closeConnectionAfterException(m_bytesRecv))
		{
			return;
		}
		
		m_recvBuff[1] = '\0';
		cout << "Time Server: Recieved: " << m_bytesRecv << " bytes of \"" << m_recvBuff << "\" message.\n";

		getFullTime(m_sendBuff);

		m_bytesSent = sendto(m_socket, m_sendBuff, (int)strlen(m_sendBuff), 0, (const sockaddr*)&m_clientAddr, m_clientAddrLen);
		if (closeConnectionAfterException(m_bytesSent))
		{
			return;
		}

		cout << "Time Server: Sent: " << m_bytesSent << "\\" << strlen(m_sendBuff) << " bytes of \"" << m_sendBuff << "\" message.\n";
	}
}

void UDPServer::getFullTime(char o_buffer[SEND_BUFFER_SIZE]) {
	time_t timer;
	time(&timer);
	strcpy(o_buffer, ctime(&timer));
	o_buffer[strlen(o_buffer) - 1] = '\0'; //to remove the new-line from the created string
}

