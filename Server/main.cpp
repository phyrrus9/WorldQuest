#include "../Common/structures.h"
#include "../Common/chunk.h"
#include "../Common/logging.h"
#include "../Common/sockets.hpp"

#include <windows.h>
#include <vector>
#include <pthread.h>
#include <string.h>

using std::vector;
vector<chunk_t *> chunklist;
vector<SOCKET> clientList;
unsigned int clientListSize = 0;

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
	unsigned long iMode = 1;
	ioctlsocket(client, FIONBIO, &iMode); //non-blocking
	clientList.push_back(client);
	clientListSize = clientList.size();
}
void *processClients(void *)
{
	log_dbg("client thread entry");
	for (;;)
	{
		if (clientListSize == 0) continue;
	}
	return NULL;
}
void *processClientRequests(void *)
{
	log_dbg("client request thread entry");
	for (;;)
	{
		if (clientListSize == 0) continue;
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
