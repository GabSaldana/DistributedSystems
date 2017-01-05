servidor.out: SocketDatagrama.o servidor.cpp
	g++ servidor.cpp -o servidor -std=c++11 SocketDatagrama.o PaqueteDatagrama.o -pthread
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h PaqueteDatagrama.o
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c