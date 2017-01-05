#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <cstdint>
#include "header.h"
#include "SocketMulticast.h"

void polygon(int , int , int , Point []);
int random(int);
int main(int argc, char const *argv[])
{
	int ld = atoi(argv[1]);
	int multi = atoi(argv[2]);
	char ip[16];
	switch(multi){
		case 1:
			strcpy(ip,GROUP_MULTICAST1);
			break;
		case 2:
			strcpy(ip,GROUP_MULTICAST2);
			break;
		case 3:
			strcpy(ip,GROUP_MULTICAST3);
			break;
		default:
			strcpy(ip,GROUP_MULTICAST0);
			break;

	}
	srand(time(0));
	Point p[MAX_LAD];
	polygon(random(800), random(600), ld , p);
	Multicast_Point mp;
	mp.lados = ld;
	memcpy ( mp.p, &p, sizeof(Point) );
	PaqueteDatagrama p1(sizeof(mp));
	SocketMulticast sm(7000);
	p1.inicializaDatos((char *)&mp);
	sm.envia(p1, 13, ip);
	return 0;
}

int random(int max){
	return rand() % max;
}

void  polygon(int x, int y, int lados, Point p[]){
	int i,radio;
    //double ang = 2*M_PI/(double)lados; //Every vertex is about "ang" degrees from each other
    //double radian = 180/M_PI;
    //double angle =60;
    srand(time(0));
    radio = 30 + random(30);
    /*for(i=0; i<lados; i++)
    {
    	printf("%lf\n",angle/radian);
    	printf("%lf\n",angle/radian);
        p[i].x = x + ceil(radio * cos(angle/radian));
        p[i].y = y + ceil(radio * sin(angle/radian));
        printf("%d,%d\n",p[i].x ,p[i].y);
        angle = angle+ang;
    }
    for(i=lados;i<10;i++){
    	p[i].x =0;
    	p[i].y=0;
    }*/
  	double a = atan2 (y, x);
    for (i = 0; i < lados; i++) {
        a = a + M_PI * 2 / lados;
        p[i].x = round ((double)x + (double)radio * cos(a));
        p[i].y = round ((double)y + (double)radio * sin(a));
       printf("%d,%d\n",p[i].x ,p[i].y);
        //line (lastx, lasty, x, y);
    }
    for(i=lados;i<10;i++){
    	p[i].x =0;
    	p[i].y=0;
    }

}