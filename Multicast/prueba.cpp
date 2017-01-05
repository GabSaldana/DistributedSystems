#include "punto.h"
#include "SocketMulticast.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

//ENVIA   g++ prueba.cpp SocketMulticast.o  PaqueteDatagrama.o -o prueba  
int main(int argc, char const *argv[])
{

	int i;
	punto p1={0,0}, p2={5,0}, p3={3,5}, p4={0,0},p5={0,0};
	figura_pac fp;
	fp.figura=TRIANGULO;
	memset (fp.puntos,0,MAX);
	fp.puntos[0]=p1;
	fp.puntos[1]=p2;
	fp.puntos[2]=p3;
	fp.puntos[3]=p4;
	fp.puntos[4]=p5;

	printf("%d\n%d\n%d\n", p1.x,p1.y,fp.figura);
	for(i=0;i<MAX;i++)
		printf(" %d\n %d\n",fp.puntos[i].x,fp.puntos[i].y);
	
	int datalen =sizeof(figura_pac);
	PaqueteDatagrama paquete(datalen);
	SocketMulticast sm(7000);
	//char mesg[4];
	//strcpy(mesg,"Hola GEOVANNI ");
	paquete.inicializaDatos((char *)&fp);

	return 0;
}