#include "SocketMulticast.h"

int main(int argc, char const *argv[])
{
	PaqueteDatagrama p1(sizeof(char)*20);
	SocketMulticast sm(7000);
	char mesg[4];
	strcpy(mesg,"Hola GEOVANNI ");
	p1.inicializaDatos(mesg);
	while(1){
		sm.envia(p1, 13);
		//printf("%s\n", p1.obtieneDatos());
	}	
	return 0;
}
