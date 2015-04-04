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

/*struct addrinfo hints, *res;
int sockfd, new_fd, activity;
struct sockaddr_in their_addr;
char message[MAXDATASIZE];
int maxsd,sd,status, yes=1;
int i =0;
int client_socket[MAXCLIENTS];
fd_set readfds; // lista de sockets a escuchar


memset(&hints,0, sizeof(hints));
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;


for(;i<MAXCLIENTS;i++){ // seteo todos los sockets de clientes a 0
	client_socket[i]=0;
}

getaddrinfo(NULL,PORT,&hints,&res);
sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);

setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof (int));


bind(sockfd,res->ai_addr,res->ai_addrlen);
freeaddrinfo(res);

printf("escuchando...\n");
listen(sockfd,BACKLOG);

socklen_t size = sizeof ( their_addr);
maxsd = sockfd;

while(1){
FD_ZERO(&readfds);
FD_SET(sockfd,&readfds);


for(i=0;i<MAXCLIENTS;i++){ // agrego todos los sockets al set
	sd = client_socket[i];
	if (sd>0) FD_SET(sd,&readfds);
	if (sd>maxsd) maxsd = sd;
}

printf("entrando a funcion select()\n");
activity = select(maxsd + 1, &readfds, NULL,NULL,NULL);

if(FD_ISSET(sockfd,&readfds)){ // un cliente quiere conectarse

	if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &size ))!=-1){
			printf("se conecto un cliente con socket %d \n",new_fd);
			send(new_fd, (void * ) "bienvenido\n", MAXDATASIZE,0);
		}
	else {
		printf("hubo un error en la conexion de un cliente\n");
		break;
	}


for(i=0;i<MAXCLIENTS;i++){ //agrega el nuevo socket al array de clientes
	if(client_socket[i]==0){
		client_socket[i] = new_fd;
		printf("Agregado a la lista de sockets como %d\n",new_fd);
		break;
	}
}

} // FIN ISSET SOCKFD

for (i =0;i<MAXCLIENTS;i++){ // hay algun mensaje de algun cliente
	sd = client_socket[i];
	if(FD_ISSET(sd,&readfds)){
		if((status = recv(new_fd, (void *) message, MAXDATASIZE, 0))==0){ // se desconecto

			printf("Cliente desconectado\n");
			close(sd);
			client_socket[i] = 0;

		}
		else {
			printf("%s",message);
		}
	}
}
}
*/
	return 0;
}



