#include <stdio.h>
#include <Socket_Cliente.h>
#include <Socket.h>
#include <stdlib.h>
main ()
{
	/*
	* Descriptor del socket y buffer para datos
	*/
	int Socket_Con_Servidor;
	char Cadena[2048];
	char ip[2048];

	/*
	* Se abre la conexion con el servidor, pasando el nombre del ordenador
	* y el servicio solicitado.
	* "localhost" corresponde al nombre del mismo ordenador en el que
	* estamos corriendo. Esta dado de alta en /etc/hosts
	* "cpp_java" es un servicio dado de alta en /etc/services
	*/
	printf("Escribe la IP:\n");
	fgets(ip,2048,stdin);
	printf("Accediendo a IP: %s",ip);
	Socket_Con_Servidor = Abre_Conexion_Inet (ip, "cpp_java");
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}

	/*
	* Se prepara una cadena con 5 caracteres y se envia, 4 letras mas
	* el \0 que indica fin de cadena en C
	*/
	Lee_Socket (Socket_Con_Servidor, Cadena, 2048);
	printf("%s",Cadena);
	printf("Escribe tu nombre\n");
	scanf("%s",Cadena);
	//strcpy (Cadena, "Hola");
	Escribe_Socket (Socket_Con_Servidor, Cadena, 2048);

	/*
	* Se lee la informacion enviada por el servidor, que se supone es
	* una cadena de 6 caracteres.
	*/
	Lee_Socket (Socket_Con_Servidor, Cadena, 2048);

	/*
	* Se escribe en pantalla la informacion recibida del servidor
	*/
	printf ("El server responde :\n %s\n", Cadena);

	/*
	* Se cierra el socket con el servidor
	*/
	//close (Socket_Con_Servidor);
}
