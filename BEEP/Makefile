CC=gcc
CCFLAGS=-Wall -Wextra

CXX=g++
CXXFLAGS=-Wall -Wextra

ALLEGROFLAGS=`allegro-config --libs`

.PHONY: all clean clear objs cristian

all: clear allegro cristian

clean:
	rm allegro cliente servidor *.o

clear:
	reset

allegro: allegro.c
	${CC} $< -o $@ ${ALLEGROFLAGS} ${CCFLAGS}

cristian: crisObjs cliente servidor

crisObjs: SocketDatagrama.cpp PaqueteDatagrama.cpp cliente.cpp servidor.cpp
	${CXX} $< -c ${CXXFLAGS}
	${CXX} $(word 2,$^) -c ${CXXFLAGS}
	${CXX} $(word 3,$^) -c ${CXXFLAGS}
	${CXX} $(word 4,$^) -c ${CXXFLAGS}

cliente: SocketDatagrama.o PaqueteDatagrama.o cliente.o
	${CXX} $^ -o $@

servidor: SocketDatagrama.o PaqueteDatagrama.o servidor.o
	${CXX} $^ -o $@
