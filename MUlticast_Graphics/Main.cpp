#include "SocketMulticast.h"
#include "punto.h"

int main(int argc, char const *argv[])
{
	figura_pac fp;
	fp.figura=TRIANGULO;

	punto p1={2,6},p2={3,5},p3={4,8},p4={0,6},p5={3,9} ;
	fp.puntos[0]=p1; fp.puntos[1]=p2; fp.puntos[2]=p3; fp.puntos[3]=p4; fp.puntos[4]=p5;

	PaqueteDatagrama p(sizeof(fp));
	SocketMulticast sm(7000);
	//char mesg[4];
	//strcpy(mesg,"Hola GEOVANNI ");
	p.inicializaDatos((char *)&fp);
	sm.envia(p, 13);
	//printf("%s\n", p1.obtieneDatos());
	return 0;
}
