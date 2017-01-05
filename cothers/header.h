#include <iostream>
using namespace std;

sem_t mutex2;
sem_t mutex3;

//codigo de inicializacion allegro
SAMPLE *audio;
int pos, vox;
int FrecuenciaActual=0;
void inicializaAllegro(){
	// Inicializa la librería de Allegro "liballeg.so.4.4.2" :
	if (install_allegro(SYSTEM_AUTODETECT, NULL, NULL)!= 0) {
	allegro_exit();
	cout<<"Error: no se puede inicializar la librería ''allegro' !"<<endl;
	exit(-1);
	}
	// Instala el módulo de sonido:
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL)!= 0) {
	allegro_exit();
	cout<<"Error: imposible la instalación del módulo de sonido !"<<endl;
	exit(-1);
	}
	// Sube el archivo wav:
	audio = load_wav("TheWeeknd.wav");
	if (!audio) {
	allegro_exit();
	cout<<"Error: imposible subir el archivo !"<<endl;
	exit(-1);
	}
	//Extrae información general del archivo wav:
	cout<<"Resolución de muestreo:bit\n"<<audio->bits<<endl;
	cout<<"Canales de salida:\n"<<audio->stereo*-1+1<<endl;
	cout<<"Frecuencia de muestreo: Hz\n"<<audio->freq<<endl;

	
}

//Variables para los sockets
int puertoOrigen=3000;
int puertoDestino=3001;
char *IPdestino;

SocketDatagrama soc(puertoOrigen);
SocketDatagrama socEscucha(puertoDestino); // c-1 le envia mensaje al 3001 y c le manda a c+1 al puerto 3001 también

struct message{
	int frecuencia;	 //indica la frecuencia de muestreo mas actual
};
//0.8 segundos es lo que se tarda en enviar a c+1 de que esta vivo c
int tEsperaEnviarSecs  =0; 
int tEsperaEnviarUsecs  =10000;
// 1 segundo es lo que espera c en esperar respuesta de c-1
int tEsperaRecibirSecs = 1 ;
int tEsperaRecibirUsecs = 0;
// hilos
void *hilo1(void*);
void *hilo2(void*);
void *hilo3(void*);