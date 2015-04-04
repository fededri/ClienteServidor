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
#define PORT "9000"
#define MAXDATASIZE 1024

int main()

{
struct addrinfo hints, * serverInfo;
int serverSocket;
char message[MAXDATASIZE];
int i;

memset(&hints,0,sizeof hints);
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;

getaddrinfo(IP,PORT,&hints,&serverInfo);

serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

if (i = connect(serverSocket,serverInfo->ai_addr,serverInfo->ai_addrlen)==-1){
	puts("Error al conectar");
}


freeaddrinfo(serverInfo);

if ((i = recv(serverSocket,(void *) message, MAXDATASIZE, 0)!=0)){
	printf ("%s",message);
}
else {
	printf("El servidor no envio nada");
}


while(1){
fgets(message,MAXDATASIZE,stdin);
if(!strcmp(message,"salir")) send(serverSocket,(void *) message, MAXDATASIZE,0 );
else {
	break;
}
}

	return 0;
}
