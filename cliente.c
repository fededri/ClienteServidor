#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define IP "127.0.0.1"
#define PORT "8500"
#define MAXDATASIZE 1024

int main()

{
struct addrinfo hints, * serverInfo;
int serverSocket;
char message[MAXDATASIZE];
int resultadoOp;

printf("Iniciando Cliente\n");
memset(&hints,0,sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;


getaddrinfo(IP,PORT,&hints,&serverInfo);
serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);


resultadoOp = connect(serverSocket,serverInfo->ai_addr,serverInfo->ai_addrlen);
freeaddrinfo(serverInfo);

if ( resultadoOp!=-1){
	printf("Conectado al servidor. Ya puede enviar mensajes, escriba 'exit' para salir\n");
}

int enviar = 1;
while(enviar){
fgets(message,MAXDATASIZE,stdin);
if(!strcmp(message,"exit\n")) enviar = 0;
if (enviar) send(serverSocket, message, strlen(message)+1,0);

}

close(serverSocket);
return 0;



}
