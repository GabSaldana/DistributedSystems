#include "SocketMulticast.h"
#include "punto.h"
#include <X11/Xos.h>
#include <X11/Xlib.h> //Every Xlib program must include this
#include <assert.h> //I include this to test return values the lazy way
#include <unistd.h> //So we got the profile for 10 seconds
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
//g++ prueba.cpp SocketMulticast.o  PaqueteDatagrama.o -o prueba
int main(int argc, char const *argv[])
{
	int opcion=0;
	opcion=atoi(argv[1]);
	punto p1,p2,p3,p4,p5,p6;
	int escala=10;
	
	figura_pac fp;
	if(opcion == 4){
		fp.figura=RECTANGULO;
		int dxr=atoi(argv[2]),dyr=atoi(argv[3]);
		/*CUADRADO*/
	punto p1={2*escala + dxr,escala*2 + dyr},p2={escala*4 + dxr,escala*2+ dyr},p3={escala*4+ dxr,escala*4+ dyr},
	p4={escala*2+dxr,escala*4+dyr},p5={escala*2+dxr,escala*2+dyr} ,p6={0*escala+dxr,escala*0+dyr};

	}
	else if(opcion == 3){
		fp.figura=TRIANGULO;
		int dxt=atoi(argv[2]),dyt=atoi(argv[3]);
		/*TRIANGULO*/
	punto p1={2*escala+dxt,escala*2+dyt},p2={escala*8+dxt,escala*2+dyt},p3={escala*5+dxt,escala*4+dyt},
	p4={escala*2+dxt,escala*2+dyt},p5={escala*0+dxt,escala*0+dyt} ,p6={0*escala+dxt,escala*0+dyt};
	}
	else if(opcion == 5){
		fp.figura=PENTAGONO;
		int dxp=atoi(argv[2]),dyp=atoi(argv[3]);
		/*PENTAGONO*/
	punto p1={2*escala+dxp,escala*3+dyp},p2={escala*2+dxp,escala*1+dyp},p3={escala*4+dxp,escala*1+dyp},
	p4={escala*5+dxp,escala*3+dyp},p5={escala*3+dxp,escala*4+dyp} ,p6={2*escala+dxp,escala*3+dyp};

	}
	else
		printf("ERROR DE OPCION\n");
	
		
	fp.puntos[0]=p1; fp.puntos[1]=p2; fp.puntos[2]=p3; fp.puntos[3]=p4; fp.puntos[4]=p5, fp.puntos[5]=p6;

	PaqueteDatagrama p(sizeof(fp));
	SocketMulticast sm(7000);
	p.inicializaDatos((char *)&fp);
	sm.envia(p, 13);
	
	return 0;
}
