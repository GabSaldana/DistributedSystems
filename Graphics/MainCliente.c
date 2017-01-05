#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include "header.h"
#include "SocketMulticast.h"

unsigned long ColorPorNombre( Display *, char * );
// gcc MainCliente.cpp -lX11 -L/usr/include/X11/Xlib -o MainC
int main(int argc, char const *argv[])
{
	Multicast_Point *mp;
	int i, thescreen;
	PaqueteDatagrama p1(sizeof(mp));
	SocketMulticast sm(7000);
	char ip[16];
	strcpy(ip,GROUP_MULTICAST0);

	Display *dpy = XOpenDisplay(NULL);

      if(dpy == NULL){

       		fprintf(stderr, "Cannot open display\n");
      		exit(1);
      }
      int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
      int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

 	Window w = XCreateSimpleWindow(dpy,DefaultRootWindow(dpy),0, 0, 800, 600,0,blackColor, blackColor);

      XSelectInput(dpy, w, StructureNotifyMask);
      XMapWindow(dpy, w);
      GC gc = XCreateGC(dpy, w, 0, NULL);
      XSetForeground(dpy, gc, whiteColor);
      for(;;) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify)
		  break;
      }
     Point p[10];
	while(1){

		sm.recive(p1, ip);
		mp=(Multicast_Point *)p1.obtieneDatos();
		memcpy(p,mp->p,sizeof(Point) );
		XPoint points[mp->lados];
		printf("Lados:%d\n",mp->lados);
		for(int i=0,j=0; i<10;i++){
			if(mp->p[i].x!=0&&mp->p[i].y!=0){
				points[j].x=p[i].x;	
				points[j].y=p[i].y;
				j++;
			}
			
		}

		for(i=0;i<=mp->lados;i++)
			printf("X:%d Y:%d \n",points[i].x,points[i].y);

		
		XSetForeground(dpy, gc, whiteColor);
		char *color=(char *)malloc(sizeof(char)*10);
		strcpy(color,"red");
		 XFillPolygon(dpy,w,gc,points,(mp->lados)+1,Complex,CoordModeOrigin);
		
      XFlush(dpy);
      usleep(500000);
      
	}
	return 0;
}
unsigned long ColorPorNombre( Display *display, char *Nombre )
{
  XColor color, temp;
  XAllocNamedColor( display,
     DefaultColormap(display,DefaultScreen(display)),
     Nombre, &color, &temp );
  return( color.pixel );
}
