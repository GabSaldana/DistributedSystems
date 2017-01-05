#ifndef SOCKETMULTICAST_H_
#define SOCKETMULTICAST_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "PaqueteDatagrama.h"

#define EMISOR 0
#define RECEPTOR 1
#define GROUP_MULTICAST "238.0.0.1"


class SocketMulticast
{
public:
	SocketMulticast(int=0);
	~SocketMulticast();
	int envia(PaqueteDatagrama &, unsigned char );
	int recive(PaqueteDatagrama &, char*);
private:
	int s;
	unsigned char Ttl;
	struct ip_mreq multicast;
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
};

#endif