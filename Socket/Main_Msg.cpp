
#include "Message.h"
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "Message.h"

int main(int argc, char const *argv[])
{

	struct messageCS m1;

	

	SocketDatagrama socket(7200);
	long tam = atol(argv[3]);
	PaqueteDatagrama p1(tam);
	p1.inicializaIp((char *)argv[1]);
	p1.inicializaPuerto(atoi(argv[2]));
	int i;

	socket.envia();
	return 0;
}
