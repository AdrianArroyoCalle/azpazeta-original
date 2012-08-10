//Divsock.cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include "divsock.h"
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

int Lee_Socket (int fd, char *Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;

	/*
	* Comprobacion de que los parametros de entrada son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{
			/* 
			* Si hemos conseguido leer datos, incrementamos la variable
			* que contiene los datos leidos hasta el momento
			*/
			Leido = Leido + Aux;
		}
		else
		{
			/*
			* Si read devuelve 0, es que se ha cerrado el socket. Devolvemos
			* los caracteres leidos hasta ese momento
			*/
			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{
				/*
				* En caso de error, la variable errno nos indica el tipo
				* de error. 
				* El error EINTR se produce si ha habido alguna
				* interrupcion del sistema antes de leer ningun dato. No
				* es un error realmente.
				* El error EGAIN significa que el socket no esta disponible
				* de momento, que lo intentemos dentro de un rato.
				* Ambos errores se tratan con una espera de 100 microsegundos
				* y se vuelve a intentar.
				* El resto de los posibles errores provocan que salgamos de 
				* la funcion con error.
				*/
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	/*
	* Se devuelve el total de los caracteres leidos
	*/
	return Leido;
}

/*
* Escribe dato en el socket cliente. Devuelve numero de bytes escritos,
* o -1 si hay error.
*/
int Escribe_Socket (int fd, char *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	/*
	* Comprobacion de los parametros de entrada
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Bucle hasta que hayamos escrito todos los caracteres que nos han
	* indicado.
	*/
	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
}
int Abre_Socket_Unix_Server (char *Servicio)
{
	struct sockaddr_un Direccion;
	int Descriptor;

	/*
	* Se abre el socket
	*/
	Descriptor = socket (AF_UNIX, SOCK_STREAM, 0);
	if (Descriptor == -1)
	 	return -1;

	/*
	* Se rellenan en la estructura Direccion los datos necesarios para
	* poder llamar a la funcion bind()
	*/
	strcpy (Direccion.sun_path, Servicio);
	Direccion.sun_family = AF_UNIX;

	if (bind (
			Descriptor, 
			(struct sockaddr *)&Direccion, 
			strlen (Direccion.sun_path) + sizeof (Direccion.sun_family)) == -1)
	{
		/*
		* En caso de error cerramos el socket y devolvemos error
		*/
		close (Descriptor);
		return -1;
	}

	/*
	* Avisamos al sistema que comience a atender peticiones de clientes.
	*/
	if (listen (Descriptor, 1) == -1)
	{
		close (Descriptor);
		return -1;
	}

	/*
	* Se devuelve el descriptor del socket servidor
	*/
	return Descriptor;
}

/*
* Se le pasa un socket de servidor y acepta en el una conexion de cliente.
* devuelve el descriptor del socket del cliente o -1 si hay problemas.
* Esta funcion vale para socket AF_INET o AF_UNIX.
*/
int Acepta_Conexion_Cliente (int Descriptor)
{
	socklen_t Longitud_Cliente;
	struct sockaddr Cliente;
	int Hijo;

	/*
	* La llamada a la funcion accept requiere que el parametro 
	* Longitud_Cliente contenga inicialmente el tamano de la
	* estructura Cliente que se le pase. A la vuelta de la
	* funcion, esta variable contiene la longitud de la informacion
	* util devuelta en Cliente
	*/
	Longitud_Cliente = sizeof (Cliente);
	Hijo = accept (Descriptor, &Cliente, &Longitud_Cliente);
	if (Hijo == -1)
		return -1;

	/*
	* Se devuelve el descriptor en el que esta "enchufado" el cliente.
	*/
	return Hijo;
}

/*
* Abre un socket servidor de tipo AF_INET. Devuelve el descriptor
*	del socket o -1 si hay probleamas
* Se pasa como parametro el nombre del servicio. Debe estar dado
* de alta en el fichero /etc/services
*/
int Abre_Socket_Inet_Server (char *Servicio)
{
	struct sockaddr_in Direccion;
	struct sockaddr Cliente;
	socklen_t Longitud_Cliente;
	struct servent *Puerto;
	int Descriptor;
	//printf("Variables inicializadas");
	/*
	* se abre el socket
	*/
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor == -1)
	 	return -1;
	//printf("Socket abierto");
	/*
	* Se obtiene el servicio del fichero /etc/services
	*/
	/*Puerto = getservbyname ("www", "tcp");
	Puerto->s_name="divelnet";
	Puerto->s_port=6996;*/
	//{"Divel Server Net";NULL;6996;"tcp";}
	
	//Puerto->s_port=6996;
	//Puerto==6996;  //Cambiar para tener puertos variables
	//if (Puerto == NULL)
		//return -1;
	//printf("Servicio obtenido");
	/*
	* Se rellenan los campos de la estructura Direccion, necesaria
	* para la llamada a la funcion bind()
	*/
	Direccion.sin_family = AF_INET;
	Direccion.sin_port = 6996;//6996;//Puerto->s_port;
	Direccion.sin_addr.s_addr =INADDR_ANY;
	//printf("Estrucura completa");
	if (bind (
			Descriptor, 
			(struct sockaddr *)&Direccion, 
			sizeof (Direccion)) == -1)
	{
		close (Descriptor);
		return -1;
	}
	//printf("Visible");
	/*
	* Se avisa al sistema que comience a atender llamadas de clientes
	*/
	if (listen (Descriptor, 1) == -1)
	{
		close (Descriptor);
		return -1;
	}
	//printf("Empezando a atender llamadas de clientes\n");
	/*
	* Se devuelve el descriptor del socket servidor
	*/
	return Descriptor;
}
int Abre_Conexion_Unix_Cliente (char *Servicio)
{
	struct sockaddr_un Direccion;
	int Descriptor;

	strcpy (Direccion.sun_path, Servicio);
	Direccion.sun_family = AF_UNIX;

	Descriptor = socket (AF_UNIX, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;

	/*
	* Devuelve 0 si todo va bien, -1 en caso de error
	*/
	if (connect (
			Descriptor, 
			(struct sockaddr *)&Direccion, 
			strlen (Direccion.sun_path) + sizeof (Direccion.sun_family)) == -1)
	{
		return -1;
	}
	else
	{
		return Descriptor;
	}
}

/*
/ Conecta con un servidor remoto a traves de socket INET
*/
int Abre_Conexion_Inet_Cliente (
	char *Host_Servidor, 
	char *Servicio)
{
	struct sockaddr_in Direccion;
	struct servent *Puerto;
	struct hostent *Host;
	int Descriptor;
	
	//Puerto = getservbyname ("www", "tcp");
	//Puerto->s_port=6996;
	//Puerto->s_name="divelnet";
	//Puerto = getservbyname (Servicio, "tcp");
	//if (Puerto == NULL)
		//return -1;
	//Puerto->s_port=6996; //Editar esto si procede
	//Host = gethostbyname ("localhost");
	//Host->h_addr=Host_Servidor;
	//if (Host == NULL)
		//return -1;
	Direccion.sin_addr.s_addr=inet_addr(Host_Servidor);

	Direccion.sin_family = AF_INET;
	//Direccion.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr; //Direccion.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr;
	Direccion.sin_port = 6996; //Direccion.sin_port = Puerto->s_port;
	
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;

	if (connect (
			Descriptor, 
			(struct sockaddr *)&Direccion, 
			sizeof (Direccion)) == -1)
	{
		return -1;
	}

	return Descriptor;
}
