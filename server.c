/*
 * server.c
 *
 *  Created on: 02/04/2015
 *      Author: federico
 */
/*
 * server.c
 * *****************************Servidor CON MULTIPLES CONEXIONES **************
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
#define PORT "8000"
#define MAXDATASIZE 1024
#define MAXCLIENTS 5


void mostrarClientes(int clientes[]);


int main()
{
struct addrinfo hints, *serverInfo;
int listenerSocket, resultadoSelect, maxSocket;
fd_set read_set;
int clientes[MAXCLIENTS], socketCliente;
struct sockaddr_in addr;
char message[MAXDATASIZE];



//inicializo el array de clientes
int i;
for(i=0;i<MAXCLIENTS;i++){
	clientes[i] = 0;
}
//*******************


memset(&hints,0, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;

getaddrinfo(NULL,PORT,&hints,&serverInfo);

listenerSocket = socket(serverInfo->ai_family,serverInfo->ai_socktype,serverInfo->ai_protocol);

printf("Escuchando desde el socket %d\n",listenerSocket);

bind(listenerSocket,serverInfo->ai_addr,serverInfo->ai_addrlen);

puts("Socket bindeado\n");

freeaddrinfo(serverInfo);
listen(listenerSocket,BACKLOG);

maxSocket = listenerSocket;
socklen_t addrlen = sizeof(addr);

while(1)
{ // MAIN WHILE
FD_ZERO(&read_set);
FD_SET(listenerSocket,&read_set);

//agregado los sockets de clientes al set
for(i=0;i<MAXCLIENTS;i++){
	if(clientes[i]>0){
		FD_SET(clientes[i],&read_set);
		
	} 
	if(clientes[i]>maxSocket) maxSocket = clientes[i];
	
}
//****************



resultadoSelect = select(maxSocket +1, &read_set,NULL,NULL,NULL);



if(resultadoSelect==-1) {
	printf("fallo el select\n");
	break;
}


if( FD_ISSET(listenerSocket,&read_set)) { // hay una conexion entrante
 socketCliente = accept(listenerSocket, (struct sockaddr*) &addr, &addrlen);

 if(socketCliente>0){
 	printf("Se conecto un cliente con socket %d\n",socketCliente);
 	send(socketCliente,"Bienvenido, escriba 'exit'para salir\n",MAXDATASIZE,0);
  					}else {
  						printf("Hubo un error en la conexion\n");
  						break;
 							}	

 for(i=0;i<MAXCLIENTS;i++){
 	if(clientes[i]==0){
 		clientes[i] = socketCliente;
 	
 		break;
 	} 

 }

} //fin manejo de conexion entrante
int statusRecv;
for(i=0;i<MAXCLIENTS;i++){
	if(FD_ISSET(clientes[i],&read_set)){ // hay un mensaje pendiente
		statusRecv = recv(clientes[i], (void *) message, MAXDATASIZE, 0);
		if(statusRecv==0 || !strcmp(message,"exit") ) // cerro conexion o quiere salir
		{
			printf("Cliente numero %d con socket %d desconectado\n",i,clientes[i]);
			close(clientes[i]);
			clientes[i]=0;			
		} else { // imprimo mensaje
			printf("%s",message);
		}

	}
}



}
	return 0;
}



void mostrarClientes(int clientes[]){
int i =0;
for(;i<MAXCLIENTS;i++){
	printf("El cliente %d contiene el socket %d\n",i,clientes[i]);
}

}
