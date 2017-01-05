#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
int main(int argc, char const *argv[])
{

	SocketDatagrama socket(7300);
	long tam = atol(argv[2]);
	char *ip ;
	ip = (char *)malloc(sizeof(char)*16);
	PaqueteDatagrama p1(tam);	
	p1.inicializaPuerto(atoi(argv[1]));
	//socket.setTimeout(0,500000);
	//socket.setBroadcast();
	socket.setBroadcast();
	socket.envia(p1);

	while(1){

		socket.recibe(p1);
		//break;
		socket.unsetBroadcast();
	strcpy(ip,p1.obtieneDireccion());
	socket.envia(p1);
	p1.inicializaIp(ip);
	socket.recibe(p1);
	}
	
	//printf("IP %s\n",ip );
	/*for(int i =100;i<255;i++){
		sprintf(ip,"192.168.0.%d", i);
		p1.inicializaIp(ip);
		printf("IP %s\n",ip );
		socket.envia(p1);
		socket.recibeTimeout(p1);
	}*/
	return 0;
}