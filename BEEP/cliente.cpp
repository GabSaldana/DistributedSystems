#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <allegro.h>
#include <sys/time.h>

#include "SocketDatagrama.hpp"
#include "PaqueteDatagrama.hpp"

#include "hdrCristian.hpp"

using namespace std;

//gcc allegro.c -o allegro `allegro-config --libs`
//void sound();

char dirIp[17] = {0};
struct timeval iniTime, finTime, delta, estTime;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Uso del programa:\n");
    //printf("  %s ipServidor ptoServidor\n\n", argv[0]);
    return 0;
  }
  
  int puerto = atoi(argv[2]);
  SocketDatagrama clSock(0);
  clSock.setTimeout(2000000); // 2 seg para el timeout
  strcpy(dirIp, argv[1]);
  
  paqCristian dataSend = {SVR_CLK, {0,0}}, *dataRecv;
  
  PaqueteDatagrama packSend((char *) &dataSend, sizeof(dataSend), dirIp, puerto);
  PaqueteDatagrama packRecv(sizeof(dataSend));
  
  clSock.envia(packSend);
  gettimeofday(&iniTime, NULL);
  
  if (clSock.recibeTimeout(packRecv) >= 0) {
    gettimeofday(&finTime, NULL);
    timersub(&finTime, &iniTime, &delta);
    
    // Recibir la hora e implementar el algoritmo de Cristian
    dataRecv = (paqCristian *) packRecv.obtieneDatos();
    
    
    if (dataRecv->opcode == OK) {
      // Todo bien, calcular el tiempo estimado para el cliente
      int64_t deltaMs = delta.tv_sec * 1000000 + delta.tv_usec;
      int64_t serverMs = (dataRecv->time).tv_sec * 1000000 + (dataRecv->time).tv_usec;
      int64_t respMs = serverMs + 0.5 * deltaMs;
      
      estTime.tv_sec = respMs / 1000000;
      estTime.tv_usec = respMs % 1000000;
     
      //estTime.tv_sec = 1283682654;
      //estTime.tv_usec = 112090 ;

    settimeofday(&estTime, NULL);

      printf("svrTime = %lu secs, %lu usecs\n", (dataRecv->time).tv_sec, (dataRecv->time).tv_usec);
      printf("delta   = %lu secs, %lu usecs\n", delta.tv_sec, delta.tv_usec);
      printf("estTime = %lu secs, %lu usecs\n", estTime.tv_sec, estTime.tv_usec);
      
      //sound();
      //settimeofday(&estTime, NULL);
    }
    
  }
  
  return 0;
}



/*void sound(){

  printf("sound\n");

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
}*/
