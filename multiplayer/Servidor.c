/*
* Javier Abellan, 20 Jun 2000
*
* Programa Servidor de socket INET, como ejemplo de utilizacion de las
* funciones de sockets.
*/
//#include <Socket_Servidor.h>
//#include <Socket.h>
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
int Abre_Socket_Unix (char *Servicio);
int Abre_Socket_Inet (char *Servicio);
int Acepta_Conexion_Cliente (int Descriptor);



int main(){

	int maximo=10;
	fd_set descriptoresLectura;
	int socketCliente[10];
	int numeroClientes; 
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena[2048];
	char nombreCliente1[1024];
	char nombreCliente2[1024];

	/*
	* Descriptores de socket servidor y de socket con el cliente
	*/

	printf("Cargando.");
	/*
	* Se abre el socket servidor, con el servicio "cpp_java" dado de
	* alta en /etc/services.
	*/
	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}
	printf(".");
	/*
	* Se espera un cliente que quiera conectarse
	*/
	socketCliente[0] = Acepta_Conexion_Cliente (Socket_Servidor);
	if (Socket_Cliente == -1)
	{
		printf ("No se puede abrir socket de cliente\n");
		exit (-1);
	}
	socketCliente[1] = Acepta_Conexion_Cliente (Socket_Servidor);
	if (Socket_Cliente == -1)
	{
		printf("No se puede abrir socket de cliente\n");
		exit(-1);
	}
	printf("2 clientes conectados");
	Escribe_Socket(socketCliente[0], "2 clientes conectados\nEmpezando juego\n", 2048);
	Escribe_Socket(socketCliente[1], "2 clientes conectados\nEmpezando juego\n", 2048);
	int correcto=1;
	int correcto2=1;
	while(correcto==1 || correcto2==1){
	correcto=Lee_Socket (socketCliente[0], nombreCliente1, 1024);
	correcto2=Lee_Socket (socketCliente[1], nombreCliente2, 1024);}
	printf(".\n");
	/*
	* Se escribe en pantalla la informacion que se ha recibido del
	* cliente
	*/
	printf ("Jugador 1: %s\n", nombreCliente1);
	printf ("Jugador 2: %s\n", nombreCliente2);

	Escribe_Socket(socketCliente[0], nombreCliente2, 1024);
	Escribe_Socket(socketCliente[1], nombreCliente1, 1024);

	/*
	* Se prepara una cadena de texto para enviar al cliente. La longitud
	* de la cadena es 5 letras + \0 al final de la cadena = 6 caracteres
	*/
	
	printf("Cerrando comunicacion\n");
	/*
	* Se cierran los sockets
	*/
	//close (Socket_Cliente); Pasado a OnQuit
	//close (Socket_Servidor);

	close (socketCliente[0]);
	close(socketCliente[1]);
	close(Socket_Servidor);
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
int Abre_Socket_Unix (char *Servicio)
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
int Abre_Socket_Inet (char *Servicio)
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
