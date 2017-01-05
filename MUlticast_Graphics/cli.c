#include "punto.h"
#include "SocketMulticast.h"
#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char const *argv[])
{

struct sockaddr_in msg_to_server_addr, client_addr, server_addr;

   int s;

   s = socket(AF_INET, SOCK_DGRAM, 0);

   bzero((char *)&server_addr, sizeof(server_addr));
/*Destinatario*/
   bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
   msg_to_server_addr.sin_family = AF_INET;
   msg_to_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip
   msg_to_server_addr.sin_port = htons(7200);//puerto
/*Remitente*/
   bzero((char *)&client_addr, sizeof(client_addr));
   client_addr.sin_family = AF_INET;
   client_addr.sin_addr.s_addr = INADDR_ANY;
   client_addr.sin_port = htons(0);
/*Lo pones a escuchar conexiones*/
   bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));

int np=15,num[np*4+3],l;
   
 //  l, x, y
   l=atoi(argv[1]);
   num[1]=atoi(argv[2]);
   num[2]=atoi(argv[3]);

   num[3]=(int)400/l;num[4]=(int)0/l;
   num[5]=(int)200/l;num[6]=(int)100/l;

   num[7]=(int)200/l;num[8]=(int)100/l;
   num[9]=(int)200/l;num[10]=(int)200/l;

   num[11]=(int)200/l;num[12]=(int)200/l;
   num[13]=(int)100/l;num[14]=(int)300/l;

   num[15]=(int)100/l;num[16]=(int)300/l;
   num[17]=(int)200/l;num[18]=(int)400/l;

   num[19]=(int)200/l;num[20]=(int)400/l;
   num[21]=(int)100/l;num[22]=(int)500/l;

   num[23]=(int)100/l;num[24]=(int)500/l;
   num[25]=(int)300/l;num[26]=(int)600/l;

   num[27]=(int)300/l;num[28]=(int)600/l;
   num[29]=(int)400/l;num[30]=(int)700/l;

   num[31]=(int)400/l;num[32]=(int)700/l;
   num[33]=(int)600/l;num[34]=(int)700/l;

   num[35]=(int)600/l;num[36]=(int)700/l;
   num[37]=(int)800/l;num[38]=(int)500/l;

   num[39]=(int)800/l;num[40]=(int)500/l;
   num[41]=(int)800/l;num[42]=(int)400/l;

   num[43]=(int)800/l;num[44]=(int)400/l;
   num[45]=(int)700/l;num[46]=(int)300/l;

   num[47]=(int)700/l;num[48]=(int)300/l;
   num[49]=(int)800/l;num[50]=(int)200/l;

   num[51]=(int)800/l;num[52]=(int)200/l;
   num[53]=(int)600/l;num[54]=(int)0/l;

   num[55]=(int)600/l;num[56]=(int)0/l;
   num[57]=(int)500/l;num[58]=(int)100/l;

   num[59]=(int)500/l;num[60]=(int)100/l;
   num[61]=(int)400/l;num[62]=(int)0/l;
   
   num[0]= sizeof(num)/sizeof(int);

   sendto(s, (char *)num, num[0] * sizeof(int ), 0, (struct sockaddr *)&msg_to_server_addr, sizeof(msg_to_server_addr));
   
      close(s);
   return 0;
}



