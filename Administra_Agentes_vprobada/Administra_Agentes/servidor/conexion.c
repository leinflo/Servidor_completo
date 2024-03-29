#include <string.h>	
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "servidor.h"
#include "baseDatos.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>


int main(){
	
	//numero de conexiones que se pueden realizar
	int conexiones = 1024;
	pthread_t child[100];

	int num_hilos = 0;

	//definicion de las estructuras del cliente y del servidor
	struct sockaddr_in direccion,cliente;
	struct param parametros[100];
	
	//identificadores de los sockets
	int _socket_,aceptacliente;
	//variables de tipo entero para diversas cosas
	int puede_conectarse,valida,opcion, n;
	//longitud de la estructura cliente;
	socklen_t clilen;
	
	char direccionIP[15],buffer[300],*hash;
	
	//creación de socket tcp para validar la conexión de los agentes y mantener una sesión con ellos. 	
	_socket_ = socket(AF_INET,SOCK_DGRAM,0);
	if(_socket_<0){
	perror("hubo un error al abrir el socket UDP\n");
	exit(1);
	}
    	printf("abriendo socket\n");
	
	//definicion de los parametros de la estructura servidor;
	direccion.sin_family = AF_INET;
	direccion.sin_port = htons(PUERTO);

	printf("asociando al puerto %d \n",PUERTO);

	//permite conexiones de cualquier agente;
	direccion.sin_addr.s_addr = INADDR_ANY;

	//bind de la direccion y el puerto
	if(bind(_socket_, (struct sockaddr *)&direccion, sizeof(direccion))<0){
	perror("hubo un error al ligar la direccion con el puerto\n");
	exit(1);
	}
    	printf("asociando socket al puerto\n");


	


	//evitar que muera el servidor
	while (1) 
	{
    	if(num_hilos<=0){
	num_hilos=0;
	}
	else{
	num_hilos--;	
	}
	    //creación de un nuevo hilo

	printf("num_hilos %d \n",num_hilos);
	
	n = recvfrom(_socket_,(char *)buffer,300,0,(struct sockaddr *)&cliente,&clilen);
	
	if(n<0){
	perror("error al recibir mensaje\n");
	}
	    printf("\n se conecto el agente %s con puerto %d\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));
	printf("tamaño %d buffer original %s  \n",n,buffer);
	bzero(&parametros[num_hilos],sizeof(parametros[num_hilos]));
	strcpy(parametros[num_hilos].direccionIP,inet_ntoa(cliente.sin_addr));
	printf("direcion IP %s \n",parametros[num_hilos].direccionIP);
	strcpy(parametros[num_hilos].mensaje,buffer);
	printf("buffer %s \n",parametros[num_hilos].mensaje);
		//recepción del primer mensaje
	//n = recv(aceptacliente,(char *)buffer,sizeof(buffer),0);
	//printf("Se recibio del agente %s\n",buffer);
	
	pthread_create(&child[num_hilos], NULL, funcionAgente,&parametros[num_hilos]); //parametros casting 

	pthread_join(&child[num_hilos], NULL);

	num_hilos++;

	printf("salio del hilo");

	}		
}


/*
void principal();

//Función para crear el demonio
int main(void) {
        
        // Our process ID and Session ID 
        pid_t pid, sid;
        
        // Fork off the parent process 
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        // If we got a good PID, then
          // we can exit the parent process. 
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        // Change the file mode mask
        umask(0);
                
        // Open any logs here     
                
        // Create a new SID for the child process
        sid = setsid();
        if (sid < 0) {
                // Log the failure 
                exit(EXIT_FAILURE);
        }
        

        
        // Change the current working directory 
        if ((chdir("/")) < 0) {
                 Log the failure 
                exit(EXIT_FAILURE);
        }
        
        // Close out the standard file descriptors 
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        
        // Daemon-specific initialization goes here 
        
        // The Big Loop 
        while (1) {
           // Do some task here ... 
           principal();
           //sleep(30);  wait 30 seconds 
        }
   exit(EXIT_SUCCESS);
}


void principal(){
	
	//numero de conexiones que se pueden realizar
	int conexiones = 1024;
	pthread_t child[100];

	int num_hilos = 0;

	//definicion de las estructuras del cliente y del servidor
	struct sockaddr_in direccion,cliente;
	struct param parametros[100];
	
	//identificadores de los sockets
	int _socket_,aceptacliente;
	//variables de tipo entero para diversas cosas
	int puede_conectarse,valida,opcion, n;
	//longitud de la estructura cliente;
	socklen_t clilen;
	
	char direccionIP[15],buffer[300],*hash;
	
	//creación de socket tcp para validar la conexión de los agentes y mantener una sesión con ellos. 	
	_socket_ = socket(AF_INET,SOCK_DGRAM,0);
	if(_socket_<0){
	perror("hubo un error al abrir el socket UDP\n");
	exit(1);
	}
    	printf("abriendo socket\n");
	
	//definicion de los parametros de la estructura servidor;
	direccion.sin_family = AF_INET;
	direccion.sin_port = htons(PUERTO);

	printf("asociando al puerto %d \n",PUERTO);

	//permite conexiones de cualquier agente;
	direccion.sin_addr.s_addr = INADDR_ANY;

	//bind de la direccion y el puerto
	if(bind(_socket_, (struct sockaddr *)&direccion, sizeof(direccion))<0){
	perror("hubo un error al ligar la direccion con el puerto\n");
	exit(1);
	}
    	printf("asociando socket al puerto\n");


	


	//evitar que muera el servidor
	while (1) 
	{
    	if(num_hilos<=0){
	num_hilos=0;
	}
	else{
	num_hilos--;	
	}
	    //creación de un nuevo hilo

	printf("num_hilos %d \n",num_hilos);
	
	n = recvfrom(_socket_,(char *)buffer,300,0,(struct sockaddr *)&cliente,&clilen);
	
	if(n<0){
	perror("error al recibir mensaje\n");
	}
	    printf("\n se conecto el agente %s con puerto %d\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));
	printf("tamaño %d buffer original %s  \n",n,buffer);
	bzero(&parametros[num_hilos],sizeof(parametros[num_hilos]));
	strcpy(parametros[num_hilos].direccionIP,inet_ntoa(cliente.sin_addr));
	printf("direcion IP %s \n",parametros[num_hilos].direccionIP);
	strcpy(parametros[num_hilos].mensaje,buffer);
	printf("buffer %s \n",parametros[num_hilos].mensaje);
		//recepción del primer mensaje
	//n = recv(aceptacliente,(char *)buffer,sizeof(buffer),0);
	//printf("Se recibio del agente %s\n",buffer);
	
	pthread_create(&child[num_hilos], NULL, funcionAgente,&parametros[num_hilos]); //parametros casting 

	pthread_join(&child[num_hilos], NULL);

	num_hilos++;

	printf("salio del hilo");

	}		
}*/


