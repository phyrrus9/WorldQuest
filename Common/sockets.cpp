#include <windows.h>
#include <winsock2.h>
#include "sockets.hpp"

static WSADATA wsa_data;

bool ws_init()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int wsaerr;
	wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
		return false;
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 )
		return false;
	wsa_data = wsaData;
	return true;
}
void ws_end()
{
	WSACleanup();
}
SOCKET ws_socket(int proto)
{
	SOCKET m_socket;
	m_socket = socket(AF_INET, SOCK_STREAM, proto);
	return m_socket;
}
SOCKET ws_tcpserver(unsigned short portno, const char *bindaddr, unsigned connectionmax)
{
	SOCKET m_socket;
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(bindaddr);
	service.sin_port = htons(portno);
	m_socket = ws_socket(IPPROTO_TCP);
	if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
		goto err;
	if (listen(m_socket, connectionmax) == SOCKET_ERROR)
		goto err;
	return m_socket;
err:
	closesocket(m_socket);
	return INVALID_SOCKET;
}
SOCKET ws_accept(SOCKET listener, struct sockaddr *out_addr)
{
	SOCKET connection;
	while ((connection = accept(listener, out_addr, NULL)) == (SOCKET)SOCKET_ERROR);
	return connection;
}
void ws_close(SOCKET sock)
{
	shutdown(sock, SD_BOTH);
}
