/*
	Archivo: SocketDatagrama.hpp
	Cabecera de la clase SocketDatagrama
	
	Se incluye la clase que implementa sockets de datagrama
*/

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
#include <unistd.h>

void alarmTriggered(int sig);

class SocketDatagrama{
	public:
		SocketDatagrama(int);
		~SocketDatagrama();					//Recibe un paquete tipo datagrama proveniente de este socket
		int recibe(PaqueteDatagrama & p);	//Envía un paquete tipo datagrama desde este socket
		int envia(PaqueteDatagrama & p);
		void setTimeout(time_t segundos, suseconds_t microsegundos);
		void unsetTimeout( );
		int recibeTimeout(PaqueteDatagrama & p);
		void setBroadcast();
		void unsetBroadcast();
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s; //ID socket
		struct timeval talarm;
		struct timeval tsend;
		struct timeval trecv;
		bool timeout;
		struct sigaction act;
		int broadcast;
};

#endif
