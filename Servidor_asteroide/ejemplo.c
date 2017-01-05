// gcc ejemplo.c -lX11 -L/usr/include/X11/Xlib -o ejemplo

#include <X11/Xos.h>
#include <X11/Xlib.h> //Every Xlib program must include this
#include <assert.h> //I include this to test return values the lazy way
#include <unistd.h> //So we got the profile for 10 seconds
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int convx(int x, int wi);
int convy(int y, int he);

void main()
{

int wi=800, he=600;

struct sockaddr_in msg_to_client_addr, server_addr;

   int s, num[63],clilen;

   s = socket(AF_INET, SOCK_DGRAM, 0);

/*Mi direccion*/
   bzero((char *)&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;//ip
   server_addr.sin_port = htons(7200);//puerto
/*Lo pones a escuchar conexiones*/
   bind(s, (struct sockaddr *)&server_addr,sizeof(server_addr));

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

	recvfrom(s,(char *)num,63*sizeof(int),
	0,(struct sockaddr *)&msg_to_client_addr,&clilen);
	int c=0;
	printf("c:%d ",c);c++;
      //Metiorito
	signed int x=-200 , y=-200;
	int x1=convx(x,wi);
	int y1=convy(y,he);

      XDrawLine(dpy, w, gc, wi/2, 0, wi/2, he );
      XDrawLine(dpy, w, gc, 0, he/2, wi, he/2);
      XDrawPoint(dpy, w, gc, x1, y1);

	XDrawLine(dpy, w, gc, convx(0,wi), convy(0,he), 
		convx(30,wi), convy(15,he));
	XDrawLine(dpy, w, gc,convx(30,wi), convy(15,he), 
		convx(0,wi), convy(30,he));
	XDrawLine(dpy, w, gc,convx(0,wi), convy(30,he), 
		convx(9,wi), convy(15,he));
	XDrawLine(dpy, w, gc,convx(9,wi), convy(15,he), 
		convx(0,wi),convy(0,he));


	int i;
	int tam=num[0];
	for(i=3; i<tam ; i+=4){
	  XDrawLine(dpy, w, gc,convx(num[i]+num[1],wi),
			convy(num[i+1]+num[2],he), 
			convx(num[i+2]+num[1],wi),
			convy(num[i+3]+num[2],he));
	}

      // Send the "DrawLine" request to the server
      XFlush(dpy);

      // Wait for 10 seconds
      sleep(10);

 }//while


}//main


int convx(int x, int wi){

int x1= wi/2 + (1*x);
return x1;

}

int convy(int y, int he){

int y1= he/2 - (1*y);
return y1;

}
