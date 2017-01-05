#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"

int main(int argc, char const *argv[])
{

	SocketDatagrama socket(7200);
	long tam = atol(argv[3]);
	PaqueteDatagrama p1(tam);
	p1.inicializaIp((char *)argv[1]);
	p1.inicializaPuerto(atoi(argv[2]));
	int i;

	char *name;

	
		socket.recibe(p1);

	return 0;
}
