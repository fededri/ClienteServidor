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
#define PORT "8000"
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

connect(serverSocket,serverInfo->ai_addr,serverInfo->ai_addrlen);
freeaddrinfo(serverInfo);

if ((i = recv(serverSocket,(void *) message, MAXDATASIZE, 0)!=0)){
	printf ("%s",message);
}



do {
fgets(message,MAXDATASIZE,stdin);
send(serverSocket,(void *) message, MAXDATASIZE,0 );
} while ((i = strcmp(message,"exit\n"))!=0);

close(serverSocket);
	return 0;
}
