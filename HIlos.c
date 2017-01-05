#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <vector>

static vector<char *> tabla;
SocketDatagrama socket(7300);
long tam = atol("5");
char *ip ;
ip = (char *)malloc(sizeof(char)*16);
PaqueteDatagrama p1(tam);	
p1.inicializaPuerto(atoi("7200"));
socket.setBroadcast();

void funcion1(void){

   printf("Hilo %d \n", (int) pthread_self());
   socket.envia(p1);
   sleep(2);
   pthread_exit(0);
}

void funcion2(void){
   while(1){

		socket.recibe(p1);
		//break;
		socket.unsetBroadcast();
		strcpy(ip,p1.obtieneDireccion());
		socket.envia(p1);
		p1.inicializaIp(ip);
		socket.recibe(p1);
	}
}

void funcion3(void){
   while(1){

		socket.recibe(p1);
		//break;
		socket.unsetBroadcast();
		strcpy(ip,p1.obtieneDireccion());
		socket.envia(p1);
		p1.inicializaIp(ip);
		socket.recibe(p1);
	}
}

int main(int argc, char const *argv[]){

	
	pthread_t th1, th2,th3;
   
   /* Se crean dos hilos con atributos predeterminados */
   pthread_create(&th1, NULL, (void *)funcion1, NULL);
   pthread_create(&th2, NULL, (void *)funcion2, NULL);
   pthread_create(&th3, NULL, (void *)funcion3, NULL);
   printf("El hilo principal espera a sus hijos\n");


}