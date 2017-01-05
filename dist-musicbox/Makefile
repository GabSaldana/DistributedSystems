CC=gcc
CFLAGS=-g -Wall -Wextra

CXX=g++
CXXFLAGS=-g -Wall -Wextra

.PHONY: all clean

all: cliente servidor

ejer1: ejer1.c
	$(CC) $^ -o $@ $(CFLAGS) `allegro-config --libs`

cliente: SocketDatagrama.cpp PaqueteDatagrama.cpp cliente.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS) -lpthread `allegro-config --libs`

servidor: SocketDatagrama.cpp PaqueteDatagrama.cpp ConcurrentList.hpp servidor.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS) -lpthread

clean:
	rm cliente servidor
