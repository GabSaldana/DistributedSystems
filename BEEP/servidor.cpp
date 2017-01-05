#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "SocketDatagrama.hpp"
#include "PaqueteDatagrama.hpp"

#include "hdrCristian.hpp"

using namespace std;

int puerto = 0;
char *dirIp = NULL;
struct timeval svrTime;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso del programa:\n");
    printf("  %s puerto\n\n", argv[0]);
    return 0;
  }
  
  int svrPto = atoi(argv[1]);
  SocketDatagrama clSock(svrPto);
  
  while (true) {
    paqCristian *dataRecv, dataSend = {NOP, {0,0}};
    PaqueteDatagrama packRecv(sizeof(*dataRecv));
    
    if (clSock.recibe(packRecv) >= 0) {
      dataRecv = (paqCristian *) packRecv.obtieneDatos();
      
      switch (dataRecv->opcode) {
        case SVR_CLK: {
          gettimeofday(&svrTime, NULL);
          dataSend.time.tv_sec = svrTime.tv_sec;
          dataSend.time.tv_usec = svrTime.tv_usec;
          dataSend.opcode = OK;
          
          printf("svrTime = %lu secs, %lu usecs\n", svrTime.tv_sec, svrTime.tv_usec);
          
          dirIp = packRecv.obtieneDireccion();
          puerto = packRecv.obtienePuerto();
          PaqueteDatagrama packSend((char *) &dataSend, sizeof(dataSend), dirIp, puerto);
          clSock.envia(packSend);
        } break;
      }
    }
  }
  
  return 0;
}
