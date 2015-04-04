/*
 * server.c
 *
 *  Created on: 02/04/2015
 *      Author: federico
 */
/*
 * server.c
 *
 *  Created on: 01/04/2015
 *      Author: federico
 */
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

#define BACKLOG 10
#define PORT "6666"
#define MAXDATASIZE 1024
#define MAXCLIENTS 10

int main(){
struct addrinfo hints, *serverInfo;
int max_descriptor = -1,resultado, socketListener, socketClient;
struct sockaddr_in addrClient;
socklen_t addrClientSize;
char message[MAXDATASIZE];
fd_set read_sockets;


memset(&hints,0,sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;


if((resultado = getaddrinfo(NULL,PORT,&hints,&serverInfo))!=0){
 puts("Error en el getaddrinfo");
}

if ((socketListener = socket(serverInfo->ai_family,serverInfo->ai_socktype,serverInfo->ai_protocol)
		 ==-1)){
	puts("Error en el socket que escucha");
}

printf("El socket que escucha es el %d\n",socketListener);



bind(socketListener, serverInfo->ai_addr , serverInfo->ai_addrlen);
freeaddrinfo(serverInfo);

puts("Escuchando...\n");
listen(socketListener,BACKLOG);
addrClientSize = sizeof (addrClient);

socketClient = accept(socketListener, (struct sockaddr*) &addrClient, &addrClientSize);

puts("Se conecto un cliente\n");
		send(socketClient,"Bienvenido\n",MAXDATASIZE,0);


/*
while (1){
FD_ZERO(&read_sockets);
FD_SET(socketListener,&read_sockets);

max_descriptor = socketListener;


if((resultado = select(max_descriptor+1, &read_sockets,NULL,NULL,NULL))==-1){
	puts("Error en select");
}
puts("Algo paso\n");
if (FD_ISSET(socketListener,&read_sockets)){ //conexion entrante

	if((socketClient = accept(socketListener, (struct sockaddr*) &addrClient, &addrClientSize))!=-1){
		puts("Se conecto un cliente\n");
		send(socketClient,"Bienvenido\n",MAXDATASIZE,0);
		}
	}

	*/

/*
if (FD_ISSET(0,&read_sockets)){
	if ( (resultado = recv(socketClient,&message,MAXDATASIZE,0)) != 0 ){
	 puts(message);
	}
	else{
		close(socketClient);
		break;
	}
}



} // fin del ciclo
*/

close(socketListener);
puts("saliendo");
	return 0;
}



