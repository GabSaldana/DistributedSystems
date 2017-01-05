
/*RECIBE DOS NUMEROS Y REGRESA LA SUMA, SERVIDOR-SUMA*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>

int puerto = 7200;

int main(int argc, char const *argv[]){
   
   int num[2];//numeros a intercambiar
   //int n=atoi(argv[1]);
   int s, res, clilen;
   struct sockaddr_in server_addr, msg_to_client_addr;//direccion de internet,
   
   s = socket(AF_INET, SOCK_DGRAM, 0);
   
   /* se asigna una direccion al socket del servidor*/
   bzero((char *)&server_addr, sizeof(server_addr));//rellenamos de n ceros a server_addr
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   printf("%x\n",puerto);
   server_addr.sin_port = htons(puerto);
   printf("%x\n",htons(puerto));
   bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
   
   clilen = sizeof(msg_to_client_addr);

   int count=10;

   while(1) {
      /*if(count == 0){
         count=10;
      }
      count--;

      if((count % 10 )== 0){
         n--;
      }*/
      recvfrom(s, (char *) num, 2*sizeof(int), 0, (struct sockaddr *)&msg_to_client_addr, &clilen);
      res = num[0] + num[1];

      printf("NUMEROS RECIBIDOS: %d %d\n",num[0],num[1] );
      
      /* envía la petición al cliente. La estructura msg_to_client_addr contiene la dirección socket del cliente */
      sendto(s, (char *)&res, sizeof(int), 0, (struct sockaddr *)&msg_to_client_addr, clilen);
   }
}

