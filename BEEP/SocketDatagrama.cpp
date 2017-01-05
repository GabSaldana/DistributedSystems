#include "SocketDatagrama.hpp"

// Sección de implementación de la clase SocketDatagrama
SocketDatagrama::SocketDatagrama(int ptoLocal) {
  s = socket(AF_INET, SOCK_DGRAM, 0);
  
  /* Prepara la dirección local (remitente) */
  bzero((char *)&direccionLocal, sizeof(direccionLocal));
  direccionLocal.sin_family = AF_INET;
  direccionLocal.sin_addr.s_addr = INADDR_ANY;
  direccionLocal.sin_port = htons(ptoLocal);

  /* Prepara la dirección foránea (destinatario) */
  bzero((char *)&direccionForanea, sizeof(direccionForanea));
  direccionForanea.sin_family = AF_INET;
  
  /* Se inicia la conexión */
  bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama() {
  // Cierra la conexión
  close(s);
}

// Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibe(PaqueteDatagrama &p) {
  unsigned int tamDirForanea = sizeof direccionForanea;
  
  int resp = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0,
    (struct sockaddr *) &direccionForanea, &tamDirForanea);
  
  p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
  p.inicializaPuerto(ntohs(direccionForanea.sin_port));
  
  return resp;
}

// Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama &p) {
  gettimeofday(&tEnvia, NULL);
  direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
  direccionForanea.sin_port = htons(p.obtienePuerto());
  
  int resp = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0,
    (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
  
  return resp;
}

void SocketDatagrama::setTimeout(long double tiempo) {
//  if (timeout == false) {
    // Activar timeout
    //segs = segundos;
    //usegs = microsegundos;
    intervalo.it_interval.tv_sec = 0;
    intervalo.it_interval.tv_usec = 0;
    intervalo.it_value.tv_sec = ((long int) tiempo) / 1000000;
    intervalo.it_value.tv_usec = ((long int) tiempo) % 1000000;
    timeout = true;
//  }
}

void SocketDatagrama::unsetTimeout() {
//  if (timeout == true) {
    // Desactivar el timeout
    //segs = 0;
    //usegs = 0;
    intervalo.it_interval.tv_sec = 0;
    intervalo.it_interval.tv_usec = 0;
    intervalo.it_value.tv_sec = 0;
    intervalo.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &intervalo, NULL);
    timeout = false;
//  }
}

void tratar_alarma(int senial) {}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama &p) {
  struct sigaction act;
  sigset_t mask;

  /* especifica el manejador */
  act.sa_handler = tratar_alarma; /*funcion a ejecutar */
  act.sa_flags = 0; /* Ninguna accion especifica */

  /* Se bloquea la señal 3 SIGQUIT */
  sigemptyset(&mask);
  sigaddset(&mask, SIGQUIT);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  sigaction(SIGALRM, &act, NULL);
  //if (segs == 0) ualarm(usegs,0);
  //else alarm(segs);
  setitimer(ITIMER_REAL, &intervalo, NULL);
  
  int resultado = recibe(p);
  
  if (resultado < 0) {
    // SIGALRM actuó. Imprimir mensaje
    tProc = intervalo.it_value;
    timeradd(&tEnvia, &tProc, &tRecibe);
    printf("[Timeout] Tiempo = %lus %luus\n", tProc.tv_sec, tProc.tv_usec);
  } else {
    // Desactivar la alarma y mostrar segundos transcurridos
    unsetTimeout();
    gettimeofday(&tRecibe, NULL);
    timersub(&tRecibe, &tEnvia, &tProc);
    printf("Tiempo transcurrido = %lus %luus\n", tProc.tv_sec, tProc.tv_usec);
  }

  tEnvia = tRecibe; // Por si se van a medir dos actos de recepción
  timerclear(&tRecibe);
  return resultado;
}

long double SocketDatagrama::recibeTProc() {
  return tProc.tv_sec * 1000000 + tProc.tv_usec;
}

void SocketDatagrama::setBroadcast() {
  broadcast = 1;
  setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
}

void SocketDatagrama::unsetBroadcast() {
  broadcast = 0;
  setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
}
