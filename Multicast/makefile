MainC.cpp: MainC.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ MainC.cpp SocketMulticast.o  PaqueteDatagrama.o -o MainC 
Main.cpp: Main.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ Main.cpp SocketMulticast.o  PaqueteDatagrama.o -o Main 
SocketMulticast.o: SocketMulticast.cpp PaqueteDatagrama.o SocketMulticast.h
	g++ SocketMulticast.cpp -c 
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c