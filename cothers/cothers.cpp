#include <iostream>
#include <semaphore.h>

//Bibliotecas para allegro
#include <allegro.h>
#include <stdlib.h>
#include <sys/time.h>

//Bibliotecas sockets e hilos 
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "header.h"  // contiene la declaracion de la estructura
#include <stdlib.h>
#include <signal.h>

using namespace std;

#include <poll.h>



int main(int argc, char const *argv[]){

	IPdestino=(char*)argv[1];

	//inicializamos lo semaforos del hilo 2 y 3
	sem_init(&mutex2,0,1);
	sem_init(&mutex3,0,0);
	//inicializamos biblioteca allegro y cargamos el audio
	inicializaAllegro(); 

	//Se crean los hilos
	pthread_t th1, th2,th3;

	
	//Se crea el hilo1 ->  sendNotifyAlive ->  le dice a C+1 que sigue vivo
	pthread_create(&th1,NULL, hilo1,NULL);		
	//Se crea el hilo2->   recibeNotifyAlive C-1 -> Checa que C-1 este vivo si 
	pthread_create(&th2,NULL, hilo2,NULL);	
	//Se crea el hilo3->   reproduceAudio -> Reproduce la canción cuando hilo3 le manda la señal
	pthread_create(&th3,NULL, hilo3,NULL);	
	


	//espera  a que los hilos terminen
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);	
	pthread_join(th3,NULL);	

	return 0;
}	

void *hilo1(void*){
	//Envia  paquete de seguir vivo cada 0.8sec
	 struct message msj;

	while(1){
		msj.frecuencia=FrecuenciaActual;
		//cout<<"Enviando notifyAlive..."<<endl;		
		PaqueteDatagrama p((char*)&msj,sizeof(message), IPdestino,puertoDestino);
		soc.envia(p);
		cout<<"Frecuencia enviada: "<<((message *)(p.obtieneDatos()))->frecuencia<<endl;
		usleep(tEsperaEnviarUsecs);
	}

	pthread_exit(0);
}

void *hilo2(void*){
		
	sem_wait(&mutex2);
	int seguirVivo=0;
	while(seguirVivo==0){
		struct pollfd fd;
		int ret;

		fd.fd = socEscucha.getIDsocket(); // your socket handler 
		fd.events = POLLIN;
		ret = poll(&fd, 1, 500); // 1 second for timeout
		switch (ret) {
		    case -1:
		        // Error
		    	cout<<"Error"<<endl;
		        break;
		    case 0:
		        // Timeout 		    	
		    	cout<<"EL OTRO SERVIDOR  HA MUERTO"<<endl;
		    	seguirVivo=1;
		        break;
		    default:
		        //Recibe mensajes de c-1 para saber en que frecuencia va
				//Espera  paquete de seguir vivo cada 0.8sec
				struct message  mensajeRespuesta;			
				
				// si c-1 se muere y ha pasado un segundo entonces c tendra que reproducir la cancion			
					cout<<"Esperando notifyAlive de c-1..."<<endl;		
					PaqueteDatagrama p(sizeof(message));
					seguirVivo=socEscucha.recibe(p);	
					memcpy( &mensajeRespuesta ,(message*)p.obtieneDatos(), sizeof(struct message) );			
					FrecuenciaActual=mensajeRespuesta.frecuencia;				
					cout<<"Paquete recibido valor :"<< FrecuenciaActual<<endl;
				seguirVivo=0;
		        break;
		}
	
	}


	
	sem_post(&mutex3);
	pthread_exit(0);	

}

void *hilo3(void*){	

	sem_wait(&mutex3);
	cout<<"Reproduciendo\n"<<endl;
	int posFinal=0;
	// Ejecuta el file wav:
	//play_sample( audio, volumen(0-255), lef-right (0-255),speed (1x,2x,), repeat != 0)
	vox = play_sample(audio, 255, 128, 1000, 0);
	voice_set_position(vox,FrecuenciaActual);
	 do {
	 	FrecuenciaActual = voice_get_position(vox);		
	 	if (FrecuenciaActual != -1){
	 		posFinal=FrecuenciaActual;
	 	}
	 } while (FrecuenciaActual!=-1);
	cout<<"Cortando reproduccion...\n"<<endl;
	cout<<"Me quede en la muestra\n"<<posFinal<<endl;

	remove_sound();

	sem_post(&mutex2);	
	pthread_exit(0);
}
