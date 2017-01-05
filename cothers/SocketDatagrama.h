#include "PaqueteDatagrama.h"
#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>

class SocketDatagrama{
public:
	SocketDatagrama(int);
	~SocketDatagrama();


	//Recibe un paquete tipo datagrama proveniente de este socket
	int recibe(PaqueteDatagrama & p);

	//Envía un paquete tipo datagrama desde este socket
	int envia(PaqueteDatagrama & p);
	void setTimeout(time_t segundos, suseconds_t microsegundos);
	void unsetTimeout( );
	int recibeTimeout(PaqueteDatagrama &p);
	int getIDsocket();
private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	struct timeval temporizador; 	
	int s; //ID socket
	bool timeout;
};
#endif