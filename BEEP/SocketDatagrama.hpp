#ifndef __SOCKDGRAM
#define __SOCKDGRAM

#include "PaqueteDatagrama.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <signal.h>
#include <cstdio>
#include <unistd.h>

class SocketDatagrama{
	public:
		SocketDatagrama(int);
		~SocketDatagrama();
		int recibe(PaqueteDatagrama & p);
		int envia(PaqueteDatagrama & p);
    void setTimeout(long double tiempo);
    void unsetTimeout();
    int recibeTimeout(PaqueteDatagrama &p);
    long double recibeTProc();
    void setBroadcast();
    void unsetBroadcast();
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s; //ID socket
        struct timeval tEnvia;
        struct timeval tRecibe;
        struct timeval tProc;
        struct itimerval intervalo;
        bool timeout;
        time_t segs;
        suseconds_t usegs;
        int broadcast;
};

#endif
