#include<stdio.h>
#include<stdlib.h>
#include<baseDatos.h>//libreria para las consultas a la base de datos
#include<sys/inet.h>
#include<string.h>
#include<registro_agentes.h>//Libreria para las opciones

int main(){

int opcion;
printf("\n\n\t\t-----------------------------------------------------------------\t\t\n\n");
printf("\t\t\n\nAdministrador de Agentes Trabajo Terminal TT2013-A047\t\t\n\n");
printf("\n\n\t\t-----------------------------------------------------------------\t\t\n\n");

while(1){
printf("\t\t\n\nSelecione la accion a realizar:\t\t\n\n");
printf("1.- Registra nuevo Agente\n");
printf("2.- Obtener Digesto\n");
printf("3.- Consulta equipos registrados\n");
printf("4.- Salir\n");
switch(opcion){
case 1:
void Registra_nuevo();
break;
}

case 2:
void Obtiene_Digesto()
break;

case 3:
void Consulta_Agentes();
break;

case 4:
exit(0);
break;

default:

printf("\t\t\n\nElija entre números del 1 al 4\t\t\n\n");
break;
}
}
