#include <allegro.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include <sys/time.h>

int main() {
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
	//audio = load_wav("DD.wav");
	audio = load_wav("rtsi-fine.wav");
	if (!audio) {
		allegro_exit();
		printf("Error: no se puede abrir el archivo.");
		exit(-1);
	}
	
	// Extrae información general del archivo wav:
	printf("Resolución de muestreo: %d bit\n", audio->bits);
	printf("Canales de salida: %d\n", audio->stereo*-1+1);
	printf("Frecuencia de muestreo: %d Hz\n", audio->freq);
	
	// Siempre que cambie el segundo

	struct timeval curtime, prevtime;
	
	gettimeofday(&curtime, NULL);
	prevtime = curtime;
	
	bool reprod = true;

//	int secs = 39;
	int secs = 0;

	while (true) {
		gettimeofday(&curtime, NULL);
		
		// Ejecuta el sonido
		if (prevtime.tv_sec != curtime.tv_sec) {
//			stop_sample(audio);

			if (reprod) {
				vox = play_sample(audio, 255, 128, 1000, 0);
				voice_set_position(vox, audio->freq * secs);
			} else {
				stop_sample(audio);
			}

			++secs;

//			if (!reprod) {
//				adjust_sample(audio, 0, 128, 1000, 0);
//			}

			reprod = !reprod;
		}
		
		prevtime = curtime;
	}

	
	// Ejecuta el file wav:
/*
	vox = play_sample(audio, 255, 128, 1000, 0);
	
	do {
		pos = voice_get_position(vox);
		printf("Ejecución de la muestra de audio n. %d\r", pos);
	} while (pos!=-1);
*/
	
	// Terminar: 
	destroy_sample(audio);
	remove_sound();
	
	return 0;
	
}
