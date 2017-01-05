#include <cstdio>
#include <cstdlib>

#include <allegro.h>

#include "messages.hpp"
#include "SocketDatagrama.hpp"
#include "PaqueteDatagrama.hpp"

int main(int argc, char *argv[]) {
	SAMPLE *audio;
	int pos, vox;
	
	// Inicializa la librería de Allegro "liballeg.so.4.4.2" :
	if (install_allegro(SYSTEM_AUTODETECT, NULL, NULL)!= 0) {
		allegro_exit();
		printf("Error: no se puede inicializar la biblioteca \"allegro\".");
		exit(-1);
	}
	
	// Instala el módulo de sonido:
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL)!= 0) {
		allegro_exit();
		printf("Error: no se puede instalar el módulo de sonido .");
		exit(-1);
	}
	
	// Sube el archivo wav:
	audio = load_wav("DD.wav");
	//audio = load_wav("rtsi-fine.wav");
	if (!audio) {
		allegro_exit();
		printf("Error: no se puede abrir el archivo.");
		exit(-1);
	}
	
	// Extrae información general del archivo wav:
	printf("Resolución de muestreo: %d bit\n", audio->bits);
	printf("Canales de salida: %d\n", audio->stereo*-1+1);
	printf("Frecuencia de muestreo: %d Hz\n", audio->freq);
	
	int numPc = atoi(argv[1]);
	char *ip = (argc >= 3) ? argv[2] : (char *) "127.0.0.1";
	int pto = (argc >= 4) ? atoi(argv[3]) : SPORT;
	
	bool reprod = false;
	
	SocketDatagrama cl(CPORT);
	
	while (true) {
		PaqueteDatagrama packRecv(sizeof(messageSC));
		cl.recibe(packRecv);
		
		messageSC *msc = (messageSC *) packRecv.obtieneDatos();
		
		Time pos = { 0, 0 };
		
		if (msc->playing == numPc) {
			if (!reprod) {
				reprod = true;
				vox = play_sample(audio, 255, 128, 1000, 0);
				voice_set_position(vox, audio->freq * (msc->point.mins * 60 + msc->point.secs));
				
				pos = msc->point;
			} else {
				int posM = voice_get_position(vox);
				
				if (posM != -1) {
					pos.secs = posM / audio->freq;
					pos.mins = pos.secs / 60;
					pos.secs %= 60;
				}
			}
		} else {
			if (reprod) {
				reprod = false;
				stop_sample(audio);
			}
		}
		
		messageCS mcs = { numPc, ACK, pos };
	
		PaqueteDatagrama packSend((char *) &mcs, sizeof mcs, ip, pto);
		cl.envia(packSend);
	}
	
	return 0;
}
