//Azpazeta Information Server
//Obtiene información de partidas en línea y tiene chat
/////////////////////////////////
#include "azpserver.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

int Lee_Socket (int fd, char *Datos, int Longitud);

int Escribe_Socket (int fd, char *Datos, int Longitud);

int main()
{
	struct AZPServerData{int level;int money;int city;char* name;int mision;int aux; int droga;int blacklist;int sobornos;} datos;
	int maximo=2;
	fd_set descriptoresLectura;
	int socketCliente[2];
	int numeroClientes; 
	int AZPServer;
	char Cadena[2048];
	char nombreCliente1[1024];
	char nombreCliente2[1024];
	struct sockaddr_in Direccion;
	struct sockaddr Cliente;
	socklen_t Longitud_Cliente;
	struct servent *Puerto;

	AZPServer=socket (AF_INET, SOCK_STREAM, 0);
	Direccion.sin_family = AF_INET;
	Direccion.sin_port = 6996;
	Direccion.sin_addr.s_addr =INADDR_ANY;
	bind (AZPServer, (struct sockaddr *)&Direccion, sizeof (Direccion));
	listen (AZPServer, 1);
	Longitud_Cliente = sizeof (Cliente);
	socketCliente[0] = accept (AZPServer, &Cliente, &Longitud_Cliente);
	socketCliente[1] = accept(AZPServer, &Cliente, &Longitud_Cliente);
	printf("2 clientes conectados");
	//Les informamos
	Escribe_Socket(socketCliente[0], "2 clientes conectados\nEmpezando juego\n", 1024);
	Escribe_Socket(socketCliente[1], "2 clientes conectados\nEmpezando juego\n", 1024);
	//Recibimos sus nombres
	Lee_Socket (socketCliente[0], nombreCliente1, 1024);
	Lee_Socket (socketCliente[1], nombreCliente2, 1024);
	//Le mostramos el nombre del otro
	Escribe_Socket(socketCliente[0], nombreCliente2, 1024);
	Escribe_Socket(socketCliente[1], nombreCliente1, 1024);

	//Cerramos la comunicación
	close (socketCliente[0]);
	close(socketCliente[1]);
	close(AZPServer);

}

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
