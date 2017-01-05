#include "SocketMulticast.h"

int main(int argc, char const *argv[])
{
	PaqueteDatagrama p1(sizeof(char)*20);
	SocketMulticast sm(7000);
	char ip[16];
	strcpy(ip,GROUP_MULTICAST);
	while(1){
		sm.recive(p1, ip);
		printf("%s\n", p1.obtieneDatos());
	}
	return 0;
}
