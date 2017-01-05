#include "SocketDatagrama.h"
#include "header.h"
#include <fcntl.h>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

const int WINDOW = 10;
char convert[1000];

//./cliente 192.168.0.132 7200 linger.wav

int main(int argc, char * argv[]){
	SocketDatagrama sock(0);
	mensajeCS mensaje;
	mensajeSC res;
	int destino;
	mensaje.opcode = READ;
	mensaje.offset = 0; 	 
	char ip[16];
	strcpy(mensaje.name,argv[3]);
	strcpy(ip,argv[1]);
	int port = atoi(argv[2]);
	if((destino = open(argv[3], O_WRONLY|O_TRUNC|O_CREAT,0666)) == -1){
       perror(argv[3]);
       exit(-1);
    }
    int enviados = 0;
    for(int i = 0; i < WINDOW; i++){
    	mensaje.opcode = READ;
    	mensaje.offset = 1000 * i;
		strcpy(mensaje.name,argv[3]);

    	PaqueteDatagrama pak((char *)&mensaje,sizeof(mensaje),ip,port);
		sock.envia(pak);
    	enviados++;
    }

    map< int, vector<char> > registro;
    int nextPack = 0;
    int nextPackToSend = WINDOW * 1000;
    int cont = WINDOW;

	PaqueteDatagrama pak1(sizeof(mensajeSC));
	while(1){
		sock.setTimeout(0, 100000);
		int result = sock.recibeTimeout(pak1);
		if(result < 0){
			mensaje.opcode = READ;
	    	mensaje.offset = nextPack;
			strcpy(mensaje.name,argv[3]);

	    	PaqueteDatagrama pak((char *)&mensaje,sizeof(mensaje),ip,port);
	    	sock.envia(pak);
			continue;
		}
		cout << result << endl;
		memcpy(&res,pak1.obtieneDatos(),sizeof(mensajeSC));

		if(res.result != OK)
			continue;
		if(res.count == 0)
			break;
		vector <char> aux(res.count);
		for(int i = 0; i < res.count; i++){
			aux[i] = res.data[i];
		}
		registro[res.offset] = aux;
		cout << "Paquete: " << res.offset / 1000 << endl;
		while(registro.find(nextPack) != registro.end()){
			
			copy(registro[nextPack].begin(), registro[nextPack].end(), convert);
			write(destino,convert,registro[nextPack].size()); 
			registro.erase(nextPack);
			nextPack += 1000;
			enviados--;
		}
		while(enviados < WINDOW){
			mensaje.opcode = READ;
	    	mensaje.offset = nextPackToSend;
			strcpy(mensaje.name,argv[3]);

	    	PaqueteDatagrama pak((char *)&mensaje,sizeof(mensaje),ip,port);
			sock.envia(pak);
	    	enviados++;
	    	nextPackToSend += 1000;
    
		}
	}
	   
   	close(destino);
   	return 0;
}

