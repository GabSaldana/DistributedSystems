#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "header.h"
#include <allegro.h>
#include <stdio.h>

void sincronizaRequest(int,PaqueteDatagrama &,SocketDatagrama &);
void sincronizaResponse(int,PaqueteDatagrama &,SocketDatagrama &);
int sound(int,int, PaqueteDatagrama &, SocketDatagrama &);
int sound2(int,int, PaqueteDatagrama &, SocketDatagrama &);
int transmicion(int,int, PaqueteDatagrama &, SocketDatagrama &);
int transmicion2(int,int, PaqueteDatagrama &, SocketDatagrama &);
int captura(int,PaqueteDatagrama &,SocketDatagrama &);
char ip[16];
int main(int argc, char const *argv[])
{

	int puerto = atoi(argv[1]);
	int order = atoi(argv[2]);
	SocketDatagrama socke(puerto),socketb(0);
	PaqueteDatagrama p1(sizeof(messageOrder)), p2(sizeof(messageSynchronizeTrack));
	if(order ==0 ){
		sincronizaRequest(order, p1, socketb);
		p2.inicializaIp(ip);	
		p2.inicializaPuerto(7200);
		sound(order, 0,p2,socke);
		/*for(;;){
			transmicion(order, 50000,p2, socke);	
		}*/
		
	}else{
		/*if(order <3){
			sincronizaResponse(order,p1, socke);
			sincronizaRequest(order, p1, socketb);
			p2.inicializaIp(ip);	
			p2.inicializaPuerto(7200);
			}else{
			sincronizaResponse(order,p1, socke);
		}*/
		sincronizaResponse(order,p1, socke);
		captura(order, p2,socke);
		
	}
	return 0;
}
int sound(int  numero, int posicion, PaqueteDatagrama &paq, SocketDatagrama &soc){

	SAMPLE *audio;
	int pos, vox;
// Inicializa la librería de Allegro "liballeg.so.4.4.2" :
	if (install_allegro(SYSTEM_AUTODETECT, NULL, NULL)!= 0) {
		allegro_exit();
		printf("Error: no se puede inicializar la librería ''allegro' !");
		exit(-1);
	}
// Instala el módulo de sonido:
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL)!= 0) {
		allegro_exit();
		printf("Error: imposible la instalación del módulo de sonido !");
		exit(-1);
	}
// Sube el archivo wav:
	audio = load_wav("01-dan-dan-kokoro-hikareteku.wav");
	if (!audio) {
		allegro_exit();
		printf("Error: imposible subir el archivo !");
		exit(-1);
	}
//Extrae información general del archivo wav:
	printf("Resolución de muestreo: %dbit\n", audio->bits);
	printf("Canales de salida: %d\n", audio->stereo*-1+1);
	printf("Frecuencia de muestreo: Hz %d\n", audio->freq);
// Ejecuta el file wav:
	vox = play_sample(audio, 255, 128, 1000, 0);
	voice_set_position(vox,posicion);
	do {
		pos = voice_get_position(vox);
		transmicion(numero , pos,paq, soc);
		printf("Ejecución de la muestra de audio n. %d\r", pos);
	} while (pos!=-1);
// Terminar:destroy_sample(audio);
	remove_sound();
return 0;
}
int sound2(int  numero, int posicion, PaqueteDatagrama &paq, SocketDatagrama &soc){

	SAMPLE *audio;
	int pos, vox;
// Inicializa la librería de Allegro "liballeg.so.4.4.2" :
	if (install_allegro(SYSTEM_AUTODETECT, NULL, NULL)!= 0) {
		allegro_exit();
		printf("Error: no se puede inicializar la librería ''allegro' !");
		exit(-1);
	}
// Instala el módulo de sonido:
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL)!= 0) {
		allegro_exit();
		printf("Error: imposible la instalación del módulo de sonido !");
		exit(-1);
	}
// Sube el archivo wav:
	audio = load_wav("01-dan-dan-kokoro-hikareteku.wav");
	if (!audio) {
		allegro_exit();
		printf("Error: imposible subir el archivo !");
		exit(-1);
	}
//Extrae información general del archivo wav:
	printf("Resolución de muestreo: %dbit\n", audio->bits);
	printf("Canales de salida: %d\n", audio->stereo*-1+1);
	printf("Frecuencia de muestreo: Hz %d\n", audio->freq);
// Ejecuta el file wav:
	vox = play_sample(audio, 255, 128, 1000, 0);
	voice_set_position(vox,posicion);
	do {
		pos = voice_get_position(vox);
		//transmicion(numero , pos,paq, soc);
		printf("Ejecución de la muestra de audio n. %d\r", pos);
	} while (pos!=-1);
// Terminar:destroy_sample(audio);
	remove_sound();
return 0;
}
int transmicion(int  numero, int posicion, PaqueteDatagrama &paq, SocketDatagrama &soc){

	messageSynchronizeTrack mesg;
	mesg.numero = numero;
	mesg.status = OK;
	mesg.posicion = posicion;
	paq.inicializaDatos((char *)&mesg);
	//printf("%d %d %d\n", mesg.numero,mesg.status,mesg.posicion);
	soc.envia(paq);
}

int transmicion2(int  numero, int posicion, PaqueteDatagrama &paq, SocketDatagrama &soc){

	messageSynchronizeTrack mesg;
	mesg.numero = numero;
	mesg.status = OK;
	mesg.posicion = posicion;
	paq.inicializaPuerto(7300);
	paq.inicializaDatos((char *)&mesg);
	//printf("%d %d %d\n", mesg.numero,mesg.status,mesg.posicion);
	soc.envia(paq);
}

int captura(int numero ,PaqueteDatagrama &paq,SocketDatagrama &soc){
	int posion=0;
	soc.setTimeout(0,250000);
	while(1){
		int x = soc.recibeTimeout(paq);
		//printf("%d\n", x);
		if(x>=0){
			messageSynchronizeTrack *mesg;
			mesg = (messageSynchronizeTrack *)paq.obtieneDatos();
			posion = mesg->posicion;
			printf("%d\n", posion);
			if(numero <3){
				transmicion(numero, posion,paq,soc);	
			}
		}
		else{
			//sleep(2);
			printf("%d\n", posion);
			if(numero <3){
				sound(order, 0,p2,soc);
			}else
			{
				sound2(numero, posion,paq,soc);		
			}
			
			break;
		}
	}
}
void sincronizaRequest(int numero,PaqueteDatagrama &paq,SocketDatagrama &soc){
		soc.setBroadcast();
		messageOrder messga;
		messga.opcion =REQUEST;
		messga.numero = numero+1;
		paq.inicializaPuerto(7200);
		paq.inicializaDatos((char *)&messga);
		//printf("Number:%d Opcion:%d Order:%d\n",numero,messga.opcion, messga.numero);
		soc.envia(paq);
		soc.recibe(paq);
		messageOrder *messgr;
		messgr = (messageOrder *)paq.obtieneDatos();
		//printf("Number:%d Opcion:%d Order:%d\n",numero,messgr->opcion, messgr->numero);
		if(messgr->numero == numero+1 && messgr->opcion == RESPONSE){
			strcpy(ip,paq.obtieneDireccion());
			printf("IP:%s Order:%d\n",ip, messgr->numero);
		}
		soc.unsetBroadcast();
}
void sincronizaResponse(int numero ,PaqueteDatagrama &paq,SocketDatagrama &soc){
	while(1){
		soc.recibe(paq);
		messageOrder *messgr;
		messgr = (messageOrder *)paq.obtieneDatos();
		//printf("Number:%d Opcion:%d Order:%d\n",numero,messgr->opcion, messgr->numero);
		if(messgr->numero == numero && messgr->opcion == REQUEST){
			messgr->opcion =RESPONSE;
			messgr->numero = numero;
			soc.envia(paq);
			break;
		}
	}
}
