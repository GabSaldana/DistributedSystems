#ifndef PAQUETEDATAGRAMA_H_
#define PAQUETEDATAGRAMA_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
class PaqueteDatagrama {
public:
	PaqueteDatagrama(char *, unsigned int, char *, int );
	PaqueteDatagrama(unsigned int );
	~PaqueteDatagrama();
	char * obtieneDireccion();          
	unsigned int obtieneLongitud();
	int obtienePuerto();
	char * obtieneDatos();
	void inicializaPuerto(int);
	void inicializaIp(char *);
	void inicializaDatos(char *);
	void MuestraDatos();
private:
	char *datos;
	char ip[16];
	unsigned int longitud;
	int puerto;  
};  
#endif