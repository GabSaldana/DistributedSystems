#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "PaqueteDatagrama.h"
class SocketDatagrama{
public:
SocketDatagrama(int =0);
~SocketDatagrama();
//Recibe un paquete tipo datagrama proveniente de este socket
int recibe(PaqueteDatagrama &p);
//Envía un paquete tipo datagrama desde este socket
int envia(PaqueteDatagrama &p);
//Temporalizador
void setTimeout(time_t, suseconds_t);
void unsetTimeout();
int recibeTimeout(PaqueteDatagrama &p);
void setBroadcast();
void unsetBroadcast();
static void tratar_alarma(int);
private:
struct sockaddr_in direccionLocal;
struct sockaddr_in direccionForanea;
int s; //ID socket
struct timeval time_lock;
struct  timeval time_ini, time_ter, time_res;
bool time_out;
};
#endif