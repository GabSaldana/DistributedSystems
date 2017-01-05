#include "SocketMulticast.h"

SocketMulticast::SocketMulticast(int port){
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s <0 ){
		exit(-1);
	}
	direccionLocal.sin_family = AF_INET;
   direccionLocal.sin_addr.s_addr = INADDR_ANY;
   direccionLocal.sin_port = htons(port);
}

SocketMulticast::~SocketMulticast(){
	close(s);
}

int SocketMulticast::envia(PaqueteDatagrama &p, unsigned char tt){
	direccionLocal.sin_addr.s_addr = inet_addr(GROUP_MULTICAST);
	Ttl = tt;
	//bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
	setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &Ttl, sizeof(Ttl));
	int send;
	send = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)); 
	if(send >=0){
		std::cout << "Envio IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto()<< std::endl;	
	}
return send;
}
int SocketMulticast::envia(PaqueteDatagrama &p, unsigned char tt, char *ip){
	direccionLocal.sin_addr.s_addr = inet_addr(ip);
	Ttl = tt;
	//bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
	setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &Ttl, sizeof(Ttl));
	int send;
	send = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)); 
	if(send >=0){
		std::cout << "Envio IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto()<< std::endl;	
	}
return send;
}

int SocketMulticast::recive(PaqueteDatagrama &p, char*ip){
	char *res;
	res = (char *)malloc(sizeof(char)*p.obtieneLongitud());
	bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
	int clilen;
	clilen = sizeof(direccionForanea);
	multicast.imr_multiaddr.s_addr = inet_addr(ip);
	multicast.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast));
	int ret = -1;
	ret = recvfrom(s, res,p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, (socklen_t*)&clilen);
	if(ret >=0){
		p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   		p.inicializaDatos(res);
   	std::cout << "Recibo IP: " << p.obtieneDireccion() << " Port:"<<p.obtienePuerto()<< std::endl;;
	}
	return ret;
}