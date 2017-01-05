#include "PaqueteDatagrama.h"
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char* data, unsigned int longi, char* dirIp , int port){
	longitud=longi;
	puerto=port;
	inicializaIp(dirIp);	
	inicializaDatos(data);
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int longi){
	longitud=longi;
	datos = new char[longitud];
}
PaqueteDatagrama::~PaqueteDatagrama(){
	cout<<"El objeto PaqueteDatagrama ha sido borrado\n";
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
char *PaqueteDatagrama::obtieneDatos(){
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int port){
	puerto = port;
}
void PaqueteDatagrama::inicializaIp(char * dirIp){
	memcpy(ip,dirIp,16*sizeof(char));
}
void PaqueteDatagrama::inicializaDatos(char * data){
	datos = new char[longitud];
	memcpy(datos,data,longitud*sizeof(char));	
}





