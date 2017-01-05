#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

pid_t pid2;

void tratar_alarma(int sig){
   printf("Proceso %d\n",getpid());
   printf("Señal %d\n Muerte del hijo\n", sig);
   sleep(1);
}
int main(int argc, char **argv)
{
   int pid, status;
   struct sigaction act; 
   /* Se crea el proceso hijo */
   pid = fork();
   switch(pid)
   {
   case -1:
      exit(-1);
   case 0:
   /* El proceso hijo ejecuta el comando solicitado */
      pid2 = getpid();
      while(1){
         printf("Hola\n");   
      }
      exit(0);
   default:
      act.sa_handler = &tratar_alarma;
      act.sa_flags=0;
      sigaction(SIGKILL,&act,NULL);
      sigaction(SIGTERM,&act,NULL);
      sleep(5);
      kill(pid2,15);
      //printf("wait...\n");
   /* Establece el manejador */
   /* Espera al proceso hijo */
   wait(&status); 
   exit(0);/* Véase con man para más detalles sobre wait */
   }
   
   exit(0);
}

