#include "SocketDatagrama.h"
SocketDatagrama::SocketDatagrama(int port){
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
   direccionLocal.sin_family = AF_INET;
   direccionLocal.sin_addr.s_addr = INADDR_ANY;
   direccionLocal.sin_port = htons(port);
   bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
   struct sigaction act;
   sigset_t mask;

	act.sa_handler = tratar_alarma;
	act.sa_flags=0;
	sigaction(SIGALRM,&act,NULL);
}
SocketDatagrama::~SocketDatagrama(){
	close(s);
}
int SocketDatagrama::envia(PaqueteDatagrama &p){
	direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   direccionForanea.sin_port = htons(p.obtienePuerto());
   gettimeofday(&time_ini, NULL);
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
void SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos){
	//time_lock.tv_sec = segundos;
	//time_lock.tv_usec = microsegundos;
	intervalo.it_interval.tv_sec =0;
	intervalo.it_interval.tv_usec =0;
	intervalo.it_value.tv_sec=segundos;
	intervalo.it_value.tv_usec=microsegundos;
	time_out = true;
}
void SocketDatagrama::unsetTimeout(){
	intervalo.it_interval.tv_sec =0;
	intervalo.it_interval.tv_usec =0;
	intervalo.it_value.tv_sec=0;
	intervalo.it_value.tv_usec=0;
	time_out = false;
}
int SocketDatagrama::recibeTimeout(PaqueteDatagrama &p){
	
	char *res;
	res = (char *)malloc(sizeof(char)*p.obtieneLongitud());
	int clilen, recv ;
	clilen = sizeof(direccionForanea);
	ualarm((time_lock.tv_sec*1000000) + time_lock.tv_usec,0);
	recv = recvfrom(s, res,p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, (socklen_t*)&clilen);
	alarm(0);
	gettimeofday(&time_ter, NULL);
	if(recv >0){
		p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   		p.inicializaDatos(res);
   	//std::cout << "IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto();
   	std::cout << "Recibo IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto()<< std::endl;;
	//std:: cout << " Datos:" <<p.obtieneDatos()<< std::endl;		
	timersub(&time_ter, &time_ini, &time_res);//res = a-b
	std::cout << "Tiempo de recibo: "<< time_res.tv_sec<<"s "<< time_res.tv_usec<<"ms"<< std::endl;
	}
		
}
void SocketDatagrama::tratar_alarma(int opc){
	std::cout << "Alarma activada"<< std::endl;
}

void SocketDatagrama::setBroadcast(){

	int yes=1;
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(int));
}
void SocketDatagrama::unsetBroadcast(){

	int yes=0;
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(int));
}
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