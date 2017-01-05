/*
	Archivo: SocketDatagrama.cpp
	Funciones de la clase SocketDatagrama
	
	Se incluyen los métodos de la clase que implementa sockets de datagrama
*/

#include "SocketDatagrama.hpp"
#include <iostream>
#include <iomanip>

#include <sys/time.h>

using namespace std;

void alarmTriggered(int sig) {
	cout << "\nTiempo de espera agotado para esta solicitud"
			<< " (triggered signal " << sig << ")" << endl;
}

SocketDatagrama::SocketDatagrama(int puertoL) {
	s = socket(AF_INET, SOCK_DGRAM, 0);
	memset( &direccionLocal, 0, sizeof direccionLocal );

	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(puertoL);		//puertoL>1024-65535, 0 puertoL aleatorio
	
	if ( bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)) == -1 )
		cout << "\nError al crear el socket.\n";
		
	act.sa_handler = ::alarmTriggered;
	act.sa_flags = 0;
	
	sigaction(SIGALRM, &act, NULL);
	
	broadcast = 0;
}

SocketDatagrama::~SocketDatagrama() {
	close(s);
}

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
	int numeroB; 	//numero de bytes leidos
	unsigned int clilen = sizeof direccionForanea;

	if ((numeroB = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &clilen)) <= 0){
		cout << "Error al recibir el mensaje.\n" << endl;
	} else {
		cout << "Mensaje recibido.\t" << numeroB << " bytes" <<endl;
		gettimeofday(&trecv, NULL);
	}

	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));

	return numeroB;
}

int SocketDatagrama::envia(PaqueteDatagrama &p) {
	memset( &direccionForanea, 0, sizeof direccionForanea );

	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());

	int numeroB;
	unsigned int clilen = sizeof direccionForanea;
	
	gettimeofday(&tsend, NULL);

	if ((numeroB = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, clilen)) == -1) {
		cout << "Error al enviar el mensaje.\n";
	} else {
		cout << "Mensaje enviado.\t" << numeroB << " bytes" <<endl;
	}

	return numeroB;
}

void SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos) {
	talarm.tv_sec = segundos;
	talarm.tv_usec = microsegundos;
	
	timeout = true;
}

void SocketDatagrama::unsetTimeout() {
	alarm(0);
	ualarm(0, 0);
	timeout = false;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p) {
	// TRIGGERED
	if (talarm.tv_sec != 0)			alarm(talarm.tv_sec);
	else if (talarm.tv_usec != 0)	ualarm(talarm.tv_usec, 0);
		
	int ans = this->recibe(p);
	
	cout << "Tiempo para recepción transcurrido: ";
	
	if (ans >= 0) {
		this->unsetTimeout();
		
		if ( timerisset(&trecv) ) {
			struct timeval tproc;
			timersub(&trecv, &tsend, &tproc);
			tsend = trecv;
			timerclear(&trecv);
			
			cout << tproc.tv_sec << "s " << tproc.tv_usec << "us" << endl;
		} else
			cout << "Desconocido." << endl;
	} else cout << talarm.tv_sec << "s " << talarm.tv_usec << "us" << endl;
	
	return ans;
}

void SocketDatagrama::setBroadcast() {
	broadcast = 1;
	setsockopt( s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast );
}

void SocketDatagrama::unsetBroadcast() {
	broadcast = 0;
	setsockopt( s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast );
}
