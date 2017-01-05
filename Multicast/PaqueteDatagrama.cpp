#include "PaqueteDatagrama.h"

PaqueteDatagrama::PaqueteDatagrama(char *cad, unsigned int longi, char *ips, int port){
	longitud = longi;
	datos = (char *)malloc(sizeof(char)*longitud);
	memcpy(datos, cad, sizeof(char )*longitud);
	strcpy(ip,ips);
	puerto= port;
}
PaqueteDatagrama::PaqueteDatagrama(unsigned int longi){
	longitud = longi;
	datos = (char *)malloc(sizeof(char)*longitud);
}
PaqueteDatagrama::~PaqueteDatagrama(){
	delete[] datos;
}

void PaqueteDatagrama::inicializaPuerto(int port){
	puerto= port;
}
void PaqueteDatagrama::inicializaIp(char *ips){
	strcpy(ip,ips);
}
void PaqueteDatagrama::inicializaDatos(char *cad){
	memcpy(datos, cad, sizeof(char )*longitud);
}
char * PaqueteDatagrama::obtieneDireccion(){
	return ip;
}
unsigned int PaqueteDatagrama::obtieneLongitud(){
	return longitud;
}
int PaqueteDatagrama::obtienePuerto(){
	return puerto;
}

char * PaqueteDatagrama::obtieneDatos(){
	return datos;
}