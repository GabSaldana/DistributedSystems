/*
	Archivo: PaqueteDatagrama.cpp
	Funciones de la clase PaqueteDatagrama
	
	Se incluyen las funciones de la clase que implementa paquetes de datagrama
*/

#include "PaqueteDatagrama.hpp"

PaqueteDatagrama::PaqueteDatagrama() {
	longitud = 0;
	puerto = 0;
}

PaqueteDatagrama::PaqueteDatagrama(char * d, unsigned int l, char* i, int p) {
	longitud = l;
	puerto = p;
	datos = new char[l];			//Se reserva el espacio para datos
	memcpy(datos, d, l);
	memcpy(ip, i, 16);
	//sizeof(algo)->total de espacio, strlen(algo)->espacio ocupado
	//longitud(total de la cadena) 
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int l) {
	datos = new char[l]; //Mensaje vacio
	longitud = l;
}

PaqueteDatagrama::PaqueteDatagrama(PaqueteDatagrama &p) {
	longitud = p.longitud;
	puerto = p.puerto;
	datos = new char[longitud];
	memcpy(datos, p.datos, longitud);
	memcpy(ip, p.ip, 16);
}

PaqueteDatagrama::~PaqueteDatagrama() {
	delete datos;
}

char* PaqueteDatagrama::obtieneDireccion() {
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud() {
	return longitud;
}

int PaqueteDatagrama::obtienePuerto() {
	return puerto;
}	

char* PaqueteDatagrama::obtieneDatos() {
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int p) {
	puerto = p;
}

void PaqueteDatagrama::inicializaIp(char * i) {
	memcpy(ip, i, 16);
}

void PaqueteDatagrama::inicializaDatos(char *d) {
	memset(datos, 0, longitud);
	memcpy(datos, d, longitud);
}
