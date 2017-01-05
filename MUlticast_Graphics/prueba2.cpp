#include "SocketMulticast.h"
#include "punto.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>
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

int convx(int x, int wi);
int convy(int y, int he);
unsigned long ColorPorNombre( Display *display, char *Nombre );
int wi=800, he=600;
int figura;
// gcc ejemplo.c -lX11 -L/usr/include/X11/Xlib -o ejemplo
int main(int argc, char const *argv[])
{
	
	figura_pac *fp;
	int i, thescreen;
	PaqueteDatagrama p1(sizeof(figura_pac));
	SocketMulticast sm(7000);
	char ip[16];
	strcpy(ip,GROUP_MULTICAST);


	punto fig_puntos[6]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
	XPoint points[6];

	//************************************************
      // Open the display
      Display *dpy = XOpenDisplay(NULL);

      if(dpy == NULL){

       		fprintf(stderr, "Cannot open display\n");
      		exit(1);
      }

      // Get some colors
      int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
      int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

      // Create the window
      Window w = XCreateSimpleWindow(dpy, 
			DefaultRootWindow(dpy), 
			0, 0, //win x,y
		        wi, he, //win w, h
			0,//win border
			 blackColor, blackColor);

      // We want to get MapNotify events
      XSelectInput(dpy, w, StructureNotifyMask);

      // "Map" the window (that is, make it appear on the screen)
      XMapWindow(dpy, w);

      // Create a "Graphics Context"
      GC gc = XCreateGC(dpy, w, 0, NULL);

      // Tell the GC we draw using the white color
      XSetForeground(dpy, gc, whiteColor);
      
      // Wait for the MapNotify event
      for(;;) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify)
		  break;
      }


	while(1){

		sm.recive(p1, ip);
		fp=(figura_pac *)p1.obtieneDatos();
		printf("FIGURA:%d\n",fp->figura);
		
		if(fp->figura == 3){//TRIANGULO
			figura=3;
			printf("TRIANGULO\n");
		}
		if(fp->figura == 4){//RECTANGULO
			figura=4;
			printf("RECTANGULO\n");
		}
		if(fp->figura == 5){//PENTAGONO
			figura=5;
			printf("PENTAGONO\n");
		}

		/*GUARDANDO PUNTOS*/
		for(i=0; i<figura;i++){
			//fig_puntos[i]=fp->puntos[i];
			points[i].x=fp->puntos[i].x;
			points[i].y=fp->puntos[i].y;
		}
		//fig_puntos[figura]=fp->puntos[0];
		points[figura].x=fp->puntos[0].x;
		points[figura].y=fp->puntos[0].y;


		for(i=0;i<figura+1;i++)
			//printf("X:%d Y:%d \n",fig_puntos[i].x,fig_puntos[i].y);
			printf("X:%d Y:%d \n",points[i].x,points[i].y);

		signed int x=-200 , y=-200;
		int x1=convx(x,wi);
		int y1=convy(y,he);
		XSetForeground(dpy, gc, whiteColor);
      	XDrawLine(dpy, w, gc, wi/2, 0, wi/2, he );
      	XDrawLine(dpy, w, gc, 0, he/2, wi, he/2);
      	XDrawPoint(dpy, w, gc, x1, y1);

      	
      	/*DIBUJANDO LOS PUNTOS
		for(i=0; i<figura ; i++){
	  		XDrawLine(dpy, w, gc,convx(points[i].x,wi),convy(points[i].y,he),convx(points[i+1].x,wi),convy(points[i+1].y,he));
	  		printf("%d\t %d\n",i,i+1);
		}*/
		char *color=(char *)malloc(sizeof(char)*10);
		strcpy(color,"red");
		 //XSetForeground(dpy, gc, ColorPorNombre(dpy, color));
		 XFillPolygon(dpy,w,gc,points,figura+1,Complex,CoordModeOrigin);
		
	// Send the "DrawLine" request to the server
      XFlush(dpy);
      sleep(10);// Wait for 10 seconds
      
	}
	return 0;
}



int convx(int x, int wi){

int x1= wi/2 + (1*x);
return x1;

}

int convy(int y, int he){

int y1= he/2 - (1*y);
return y1;

}

unsigned long ColorPorNombre( Display *display, char *Nombre )
{
  XColor color, temp;
  XAllocNamedColor( display,
     DefaultColormap(display,DefaultScreen(display)),
     Nombre, &color, &temp );
  return( color.pixel );
}