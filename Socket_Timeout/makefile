Main.cpp: Main.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ Main.cpp SocketDatagrama.o  PaqueteDatagrama.o -o Main
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c 
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c