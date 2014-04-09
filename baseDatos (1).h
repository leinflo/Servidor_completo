/*Funciones para validar en la base de datos conexiones*/
void AlmacenaProcesos(char *cadena,char *direccionIP);
void AlmacenaArchivos(char *cadena,char *direccionIP);
void AlmacenaEquipoNuevo(char *direccionIP);
int ValidaEquipo(char *direccionIP, char *digesto);
int Conectado(char *direccionIP);
int PuedeConectarse(char *direccionIP);
void ObtieneDigesto(char *direccionIP);
void Consulta_Agentes();
int isIpv4(char ip[15]);

