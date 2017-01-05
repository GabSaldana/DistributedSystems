#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int puerto = 7200;

int main(void)
{
   struct sockaddr_in msg_to_server_addr, client_addr, server_addr;
   int s, num[2], res;
   char ip[20];
   int clilen;
   s = socket(AF_INET, SOCK_DGRAM, 0);
   //printf("Ingresa dirección ip servidor\n");
   //gets(ip);
   /* rellena la dirección del servidor */
   bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
   bzero((char *)&server_addr, sizeof(server_addr));
   msg_to_server_addr.sin_family = AF_INET;
   msg_to_server_addr.sin_addr.s_addr = inet_addr("192.168.0.112");
   msg_to_server_addr.sin_port = htons(puerto);
  /* memcpy(ip, inet_ntoa(msg_to_server_addr.sin_addr)an, sizeof(char )*15);
   printf("%s\n", ip);*/
   /* rellena la direcciòn del cliente*/
   bzero((char *)&client_addr, sizeof(client_addr));
   client_addr.sin_family = AF_INET;
   client_addr.sin_addr.s_addr = INADDR_ANY;
   
   /*cuando se utiliza por numero de puerto el 0, el sistema se encarga de asignarle uno */
   client_addr.sin_port = htons(11000);
   bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));
   num[0] = 2;
   num[1] = 5; /*rellena el mensaje */
   clilen = sizeof(server_addr);
   sendto(s, (char *)num, 2 * sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr, sizeof(msg_to_server_addr));
   
   /* se bloquea esperando respuesta */
   recvfrom(s, (char *)&res, sizeof(int), 0, (struct sockaddr *) &server_addr, &clilen);
   memcpy(ip, inet_ntoa(server_addr.sin_addr), sizeof(char )*15);
   printf("IP: %s Port:%d\n", ip, ntohs(server_addr.sin_port));
   printf("2 + 5 = %d\n", res);
   close(s);
}

