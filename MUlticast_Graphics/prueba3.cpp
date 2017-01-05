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
#include <time.h>
#include <math.h>

using namespace std;
int rangeRandomAlg2 (int max);
//g++ prueba.cpp SocketMulticast.o  PaqueteDatagrama.o -o prueba
int main(int argc, char const *argv[])
{
	//int opcion=0;
	//opcion=atoi(argv[1]);
	//punto p1,p2,p3,p4,p5,p6;
	SocketMulticast sm(7000);	
	srand(time(0));
	int escala=10;
	figura_pac fp;
	fp.figura=RECTANGULO;
	int wi=800, he=600;
while(1){	
	int dxr= rangeRandomAlg2(he);
	int dyr= rangeRandomAlg2(he);

	/*CUADRADO*/
	punto p1={2*escala + dxr,escala*2 + dyr},p2={escala*4 + dxr,escala*2+ dyr},p3={escala*4+ dxr,escala*4+ dyr},
	p4={escala*2+dxr,escala*4+dyr},p5={escala*2+dxr,escala*2+dyr} ,p6={0*escala+dxr,escala*0+dyr};
		
	fp.puntos[0]=p1; fp.puntos[1]=p2; fp.puntos[2]=p3; fp.puntos[3]=p4; fp.puntos[4]=p5, fp.puntos[5]=p6;
	PaqueteDatagrama p(sizeof(fp));
	p.inicializaDatos((char *)&fp);
	sm.envia(p, 13);
}
	
	return 0;
}


int rangeRandomAlg2 (int max){
 
 	return rand() % max ;  
}