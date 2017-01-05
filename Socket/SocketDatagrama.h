#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include "PaqueteDatagrama.h"

class SocketDatagrama{
public:
SocketDatagrama(int =0);
~SocketDatagrama();
//Recibe un paquete tipo datagrama proveniente de este socket
int recibe(PaqueteDatagrama &p);
//Envía un paquete tipo datagrama desde este socket
int envia(PaqueteDatagrama &p);
//ASocia un temporizador al socket
void setTimeout(int segundos, int microsegundos);
//Desactiva el timeout deja al socket como inicialmente
void unsetTimeout();
//Obtiene el valor de revfrom si es negativo SIGALARM ha desbloqueado , si es positivo el valor se desactiva la alarma
void recibeTimeout(PaqueteDatagrama &p);
private:
struct sockaddr_in direccionLocal;
struct sockaddr_in direccionForanea;
struct timeval time;//temporizador
int s; //ID socket
bool timeout=0;

};
#endif