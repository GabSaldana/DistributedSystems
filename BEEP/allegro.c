#include <allegro.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>


//gcc allegro.c -o allegro `allegro-config --libs`
void sound();

int main() {
  
  sound();
  return 0;
}


void sound(){

  struct timeval current_time, new_time;
  gettimeofday(&current_time, NULL);
  
  // Inicializa la librería de Allegro "liballeg.so.4.4.2" :
  if (install_allegro(SYSTEM_AUTODETECT, NULL, NULL) != 0) {
    allegro_exit();
    printf("Error: no se puede inicializar la librería 'allegro' !\n");
    exit(-1);
  }
  
  // Instala el módulo de sonido:
  if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
    allegro_exit();
    printf("Error: imposible la instalación del módulo de sonido !\n");
    exit(-1);
  }
  
  SAMPLE *audio;
  int pos, vox;
  
  // Sube el archivo wav:
  audio = load_wav("beep.wav");
  if (!audio) {
    allegro_exit();
    printf("Error: imposible subir el archivo !");
    exit(-1);
  }

  //Extrae información general del archivo wav:
  printf("Resolución de muestreo: %d bit\n", audio->bits);
  printf("Canales de salida: %d\n", audio->stereo*-1+1);
  printf("Frecuencia de muestreo: %d Hz\n", audio->freq);
  
  while (1) {
    gettimeofday(&new_time, NULL);
        
    if (new_time.tv_sec != current_time.tv_sec) {

      // Ejecuta el file wav:
      vox = play_sample(audio, 255, 128, 1000, 0);
      do {
        pos = voice_get_position(vox);
        printf("Ejecución de la muestra de audio n. %d\r", pos);
      } while (pos!=-1);
      
      printf("\n\n");
    }
    
    current_time = new_time;
  }
  // Terminar:
  destroy_sample(audio);
  remove_sound();
}
