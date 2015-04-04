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
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define BACKLOG 10
#define PORT "9000"
#define MAXDATASIZE 1024
#define MAXCLIENTS 10

int main(){
struct addrinfo hints, *serverInfo;
int max_descriptor = -1,resultado, socketClient;
struct sockaddr_in addrClient;
socklen_t addrClientSize;
char message[MAXDATASIZE];
fd_set read_sockets;


memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// No importa si uso IPv4 o IPv6
	hints.ai_flags = AI_PASSIVE;		// Asigna el address del localhost: 127.0.0.1
	hints.ai_socktype = SOCK_STREAM;	


resultado = getaddrinfo(NULL,PORT,&hints,&serverInfo);


int listenningSocket;
	listenningSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

printf("El socket que escucha es el %d\n",listenningSocket);



bind(listenningSocket,serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo); // Ya no lo vamos a necesitar

puts("Escuchando...\n");
listen(listenningSocket, BACKLOG);
struct sockaddr_in addr;			// Esta estructura contendra los datos de la conexion del cliente. IP, puerto, etc.
	socklen_t addrlen = sizeof(addr);

if( (socketClient = accept(listenningSocket, (struct sockaddr *) &addr, &addrlen)!=-1)) {
	puts("Se conecto un cliente\n");
		send(socketClient,"Bienvenido\n",MAXDATASIZE,0);
}

int status = 1;
	while (status != 0){
		status = recv(socketClient, (void*) message, MAXDATASIZE, 0);
		if (status != 0) printf("%s", message);

	} 



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

close(listenningSocket);
puts("saliendo");
	return 0;
}



