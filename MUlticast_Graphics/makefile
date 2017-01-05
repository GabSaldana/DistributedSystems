prueba2.cpp: prueba2.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ prueba2.cpp -lX11 -L/usr/include/X11/Xlib SocketMulticast.o  PaqueteDatagrama.o -o prueba2
prueba.cpp: prueba.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ prueba.cpp SocketMulticast.o  PaqueteDatagrama.o -o prueba 
SocketMulticast.o: SocketMulticast.cpp PaqueteDatagrama.o SocketMulticast.h
	g++ SocketMulticast.cpp -c 
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
