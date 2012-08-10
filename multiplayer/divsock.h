#ifndef _DIVSOCK_H
#define _DIVSOCK_H

int Lee_Socket (int fd, char *Datos, int Longitud);
int Escribe_Socket (int fd, char *Datos, int Longitud);
int Abre_Conexion_Unix_Cliente (char *Servicio);
int Abre_Conexion_Inet_Cliente (char *Host_Servidor, char *Servicio);
int Abre_Socket_Inet_Server (char *Servicio);
int Abre_Socket_Unix_Server (char *Servicio);
int Acepta_Conexion_Cliente (int Descriptor);


#endif
