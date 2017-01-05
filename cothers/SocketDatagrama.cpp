#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

using namespace std;

struct timeval t0;
struct timeval t1;

void tratar_alarma(int valor){
	cout<<"Alarma recibida ";
}

SocketDatagrama::SocketDatagrama(int pto)
{
	//creamos el socket de datagrama
	s = socket(AF_INET, SOCK_DGRAM,0);
	bzero((char*)&direccionLocal, sizeof(direccionLocal));
	// le cargamos los datos
	direccionLocal.sin_family=AF_INET;
	direccionLocal.sin_addr.s_addr=INADDR_ANY;
	direccionLocal.sin_port=htons(pto);
	//Se asocia el socket
	bind(s,(struct sockaddr*)&direccionLocal,sizeof(direccionLocal));

}

SocketDatagrama::~SocketDatagrama()
{
	cout << "Se ha cerrado la conexion\n";
	close(s);
}

//Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibe(PaqueteDatagrama &p)
{
	bzero((char*)&direccionForanea, sizeof(direccionForanea));
	socklen_t clilen= (socklen_t )sizeof(direccionForanea);

	//bzero((char*)&direccionForanea, sizeof(direccionForanea));
	cout <<"Esperando mensaje...\n";
	//se almacena valor de fucion para ser retornado	
	int r = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(),0,(struct sockaddr*)&direccionForanea ,&clilen);
	cout <<"Paquete recibido!!\n";
	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));	
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));
	
	return r;
}

//Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama &p)
{
	socklen_t tamdir = sizeof(direccionForanea);

	bzero((char*)&direccionForanea, sizeof(direccionForanea));
	// le cargamos los datos
	direccionForanea.sin_family=AF_INET;
	direccionForanea.sin_addr.s_addr=inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port=htons(p.obtienePuerto());
	
	cout <<"Enviando paquete...\n";
	//Se envía la información

	

	int r = sendto(s,p.obtieneDatos(),p.obtieneLongitud(),0,(struct sockaddr*)&direccionForanea,tamdir);	
	cout <<"Paquete enviado!!\n";
	return r;
}



void  SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos){

	//rellenamos la estructura 
	temporizador.tv_sec=segundos;
	temporizador.tv_usec=microsegundos;
	//activamos al alarma
	timeout=true;
}

void  SocketDatagrama::unsetTimeout( ){
	timeout=false;
}
int  SocketDatagrama::recibeTimeout(PaqueteDatagrama &p){

	bzero((char*)&direccionForanea, sizeof(direccionForanea));
	socklen_t clilen= (socklen_t )sizeof(direccionForanea);

	struct sigaction act;
	sigset_t mask;

	act.sa_handler = tratar_alarma;/*funcion a ejecutar cuando se reciba la señal*/
	act.sa_flags = 0;/*Ninguna accion a tomar en específica*/
	
	sigemptyset(&mask);	
	sigprocmask(SIG_SETMASK,&mask,NULL);
	sigaction(SIGALRM,&act,NULL);

	gettimeofday(&t0,NULL);
	if ( temporizador.tv_sec == 0 ){
		ualarm(temporizador.tv_usec,0);
	}
	else{
		alarm(temporizador.tv_sec );/*se arma el temporizador*/
	}
	cout <<"enviando señal...\n";
	int r;
	cout <<"Esperando mensaje...\n";
	
	//se almacena valor de fucion para ser retornado	
	r= recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(),0,(struct sockaddr*)&direccionForanea ,&clilen);

	

	if ( r == -1 ){

		cout <<"Tiempo para recepcion  agotado. \n";
		cout <<"Tiempo de alarma:. \n";

		cout <<temporizador.tv_sec<<"s "<<temporizador.tv_usec<<"usec\n" ;
		unsetTimeout();

	}else{

		if ( temporizador.tv_sec == 0 ){
			ualarm(0,0);
		}
		else{
			alarm(0 );/*se arma el temporizador*/
		}		
		unsetTimeout(); // se desactiva la alarma en el socket

		gettimeofday(&t1,NULL);
		struct timeval result;
		timersub(&t1,&t0,&result);
		cout <<"Recepcion finalizada en : ";
		cout <<result.tv_sec<<"s "<<result.tv_usec<<"usec";

		cout <<"Paquete recibido!!\n";
		p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));	
		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
	}



	
	return r;
	
	
}


int SocketDatagrama::getIDsocket(){
	return s;
}



