#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void tratar_alarma(int sig){
	printf("Alarma Activada\n");
	printf("Proceso%d\n",getpid());
	if(sig == 20){
		printf("Me han intentado detener\n");
		sleep(1); 
	}
	printf("Señal %d\n", sig);
	sleep(1);
}
int main(int argc, char const *argv[])
{
	struct sigaction act;
	sigset_t mask;//mascara de señales bloqueadas durante la ejecucion del manejador

	act.sa_handler = &tratar_alarma;//accion a ejecutar
	act.sa_flags=0;
	sigfillset(&mask);//inicializacion de un conjunto no vacio de señales 
	sigemptyset(&mask);//inicializacion de un conjunto vacio de señales 
	sigdelset(&mask,SIGQUIT);//elimando una señal
	sigprocmask(SIG_SETMASK,&mask,NULL);//activa o desactiva a mascara
	sigaction(SIGALRM,&act,NULL);//armamos una señal
	sigaction(SIGQUIT,&act,NULL);
	sigaction(SIGTSTP,&act,NULL);
	for (; ;)
	{
		printf("Linea 1\n");
		ualarm(50000,0);//espera medio seg
		printf("Linea 2\n");
		pause();//bloquea un proceso hasta que llegue una señal desbloqueante (kill)
		kill(getpid(),3);//matando al proceso con la señal kill
		printf("Linea 3\n");
	}
	return 0;
}
