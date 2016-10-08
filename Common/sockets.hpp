#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdlib.h>

#define IPPROTO_TCP 6
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

typedef unsigned int u_int;
typedef u_int SOCKET;

bool ws_init();
void ws_end();
SOCKET ws_socket(int proto = IPPROTO_TCP);
SOCKET ws_tcpserver(unsigned short portno = 80, const char *bindaddr = "127.0.0.1", unsigned connectionmax = 10);
SOCKET ws_accept(SOCKET listener, struct sockaddr *out_addr = NULL);
void ws_close(SOCKET sock);

#endif
