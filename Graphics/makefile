MainCliente.cpp: MainCliente.c SocketMulticast.o PaqueteDatagrama.o
	gcc MainCliente.c -lX11 -L/usr/include/X11/Xlib SocketMulticast.o  PaqueteDatagrama.o -o MainCliente
Main.cpp: Main.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ Main.cpp SocketMulticast.o  PaqueteDatagrama.o -o Main 
SocketMulticast.o: SocketMulticast.cpp PaqueteDatagrama.o SocketMulticast.h
	g++ SocketMulticast.cpp -c 
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c



