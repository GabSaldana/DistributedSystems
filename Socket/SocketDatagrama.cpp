#include "SocketDatagrama.h"

SocketDatagrama::SocketDatagrama(int port){
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
   direccionLocal.sin_family = AF_INET;
   direccionLocal.sin_addr.s_addr = INADDR_ANY;
   direccionLocal.sin_port = htons(port);
   bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama(){
	close(s);
}

int SocketDatagrama::envia(PaqueteDatagrama &p){
	direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   direccionForanea.sin_port = htons(p.obtienePuerto());
   sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, sizeof(direccionForanea));
   std::cout << "Envio IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto()<< std::endl;;
	//std:: cout << " Datos:" <<p.obtieneDatos()<< std::endl;
}

int SocketDatagrama::recibe(PaqueteDatagrama &p){
	char *res;
	res = (char *)malloc(sizeof(char)*p.obtieneLongitud());
	int clilen;
	clilen = sizeof(direccionForanea);
	recvfrom(s, res,p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, (socklen_t*)&clilen);	
	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   	p.inicializaDatos(res);
   	//std::cout << "IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto();
   	std::cout << "Recibo IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto()<< std::endl;;
	//std:: cout << " Datos:" <<p.obtieneDatos()<< std::endl;
}

//activar el timeout
void SocketDatagrama::setTimeout(int segundos, int microsegundos){

	time.time_t=segundos;
	time.suseconds_t=microsegundos;
	timeout=1;

}

//desactivar el timeout
void unsetTimeout(){

	time.time_t=0;
	time.suseconds_t=0;
	timeout=0;
	//dejar al socket en el estado inicial
}

void recibeTimeout(PaqueteDatagrama &p){

char *res;
	int r;
	res = (char *)malloc(sizeof(char)*p.obtieneLongitud());
	int clilen;
	clilen = sizeof(direccionForanea);
	r=recvfrom(s, res,p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, (socklen_t*)&clilen);

	if(r<0){

		printf("Tiempo para recepcion transcurrido: %d con %d us",time.time_t,time.suseconds_t);
	}else{
		unsetTimeout();
	}
}

recibeTimeout(PaqueteDatagrama &p);
/*int main(int argc, char const *argv[])
{
	SocketDatagrama socket(7200);
	PaqueteDatagrama p1(2 * sizeof(int)),p2(sizeof(int));
	int num[2];
	int msg;
	while(1){
		socket.recibe(p1);
		p2.inicializaIp(p1.obtieneDireccion());
		p2.inicializaPuerto(p1.obtienePuerto());
		msg = 7;
		p2.inicializaDatos((char *)&msg);
		socket.envia(p2);
	}
	return 0;
}*/