all:	objetos
	g++ cothers.cpp -lpthread PaqueteDatagrama.o SocketDatagrama.o -o cothers `allegro-config --libs`
objetos:
	g++ PaqueteDatagrama.cpp -c
	g++ SocketDatagrama.cpp -c
