#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("Sistema de lectura de ShellBang de Unix\n");
	getchar();
	printf("%s muestra lo siguiente\n",argv[1]);
	getchar();
	getchar();
	FILE* archivo=fopen(argv[1],"r");
	while(!feof(archivo)){
	char letra=fgetc(archivo);
	printf("%c",letra);



	
	}
	return 0;

}
