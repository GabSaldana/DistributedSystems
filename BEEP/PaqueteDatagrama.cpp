#include "PaqueteDatagrama.hpp"

// Sección de implementación de la clase PaqueteDatagrama
PaqueteDatagrama::PaqueteDatagrama(char *data, unsigned int tamData, char *ipSend, int ptoSend) {
  longitud = tamData;
  datos = new char[longitud];
  memcpy(datos, data, longitud);
  memcpy(ip, ipSend, 16);
  puerto = ptoSend;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int tamData) {
  longitud = tamData;
  datos = new char[longitud];
  memset(datos, '\0', longitud);
}

PaqueteDatagrama::~PaqueteDatagrama() {
  delete datos;
}

char * PaqueteDatagrama::obtieneDireccion() {
  return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud() {
  return longitud;
}

int PaqueteDatagrama::obtienePuerto() {
  return puerto;
}

char * PaqueteDatagrama::obtieneDatos() {
  return datos;
}

void PaqueteDatagrama::inicializaPuerto(int pto) {
  puerto = pto;
}

void PaqueteDatagrama::inicializaIp(char *ipNum) {
  memcpy(ip, ipNum, 16);
}

void PaqueteDatagrama::inicializaDatos(char *data) {
  memset(datos, '\0', longitud);
  memcpy(datos, data, longitud);
}
