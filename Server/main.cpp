#include "../Common/structures.h"
#include "../Common/chunk.h"
#include "../Common/logging.h"

#include <windows.h>
#include <winsock2.h>
#include <vector>
#include <pthread.h>

using std::vector;
WSADATA wsa_data;
vector<chunk_t *> chunklist;
vector<SOCKET> clientList;

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
SOCKET ws_socket(int proto = IPPROTO_TCP)
{
	SOCKET m_socket;
	m_socket = socket(AF_INET, SOCK_STREAM, proto);
	return m_socket;
}
SOCKET ws_tcpserver(unsigned short portno = 80, const char *bindaddr = "127.0.0.1", unsigned connectionmax = 10)
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
SOCKET ws_accept(SOCKET listener, struct sockaddr *out_addr = NULL)
{
	SOCKET connection;
	while ((connection = accept(listener, out_addr, NULL)) == (SOCKET)SOCKET_ERROR);
	return connection;
}
void ws_close(SOCKET sock)
{
	shutdown(sock, SD_BOTH);
}
chunk_t *init_chunk(int x, int y, int z)
{
	chunk_t *ret;
	ret = new chunk_t;
	memset(ret, 0, sizeof(chunk_t));
	ret->startx = x;
	ret->starty = y;
	ret->startz = z;
	return ret;
}
unsigned int add_chunk(chunk_t *chunk)
{
	chunk->chunkid = chunklist.size();
	chunklist.push_back(chunk);
	return chunk->chunkid;
}
void addClient(SOCKET client)
{
	u_long iMode = 1;
	ioctlsocket(client, FIONBIO, &iMode); //non-blocking
	clientList.push_back(client);
}
void *processClients(void *)
{
	log_xtra("client thread entry");
	for (;;)
	{
		if (clientList.size() == 0) continue;
	}
	return NULL;
}
void *processClientRequests(void *)
{
	log_xtra("client request thread entry");
	for (;;)
	{
		if (clientList.size() == 0) continue;
	}
	return NULL;
}
int main()
{
	SOCKET server;
	pthread_t processThread, requestThread;
	log_set(LOGGING_ALL);
	log_info("Setting up server");
	if (!ws_init())
	{
		log_err("Failed to initialize WinSock2!");
		return -1;
	}
	server = ws_tcpserver(25010, "127.0.0.1", 250);
	pthread_create(&processThread, NULL, processClients, NULL);
	pthread_create(&requestThread, NULL, processClientRequests, NULL);
	for (;;)
	{
		if (clientList.size() < 250)
			addClient(ws_accept(server));
	}
	while (!clientList.size()); //wait for all clients to be shutdown
	ws_end();
	log_info("Exiting server");
	return 0;
}
