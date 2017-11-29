#include "header.h"

void nombre_archivo(char **nombre){

	*nombre = malloc( sizeof( char) * strlen( optarg)); //reservamos el tamaño del nombre del archivo de configuracion
	strcpy( *nombre, optarg);

}


int parser_puerto(char *archivo){

	char buffer[800];
	memset(buffer,0,800);

	char *buf;
	int puerto;
	int fd;

	fd = open(archivo,O_RDONLY);
	read (fd,buffer,sizeof(buffer));
	close (fd);
//	printf("lo que se leyo del archivo es:\n");
//	write(1,buffer,sizeof(buffer));

	if ( !strncmp (buffer, "port", 4 )) {
		buf = strtok( buffer, "=" ); // primer token (puerto)

	//	printf("primer token del parseo puerto: = \n");
	//	write(1,buffer,sizeof(buffer));
	//	printf("\n");
	//	printf( "%s\n", buf );

		buf = strtok( NULL, "\n" ); // segundo token (numero puerto)

	//	printf("segundo token del parseo puerto: n \n");
        //         write(1,buffer,sizeof(buffer));
	//	printf("\n");
	//	printf( "%s\n", buf );

		puerto = atoi(buf);
	}

	//printf ("puerto %d\n",puerto);
	return puerto;

} // fin funcion ParserPuerto

char *parser_ruta(char *archivo){

	char buffer[800];
	memset(buffer,0,800);
	int fd;

	fd = open(archivo,O_RDONLY);
	read (fd,buffer,sizeof(buffer));
	close (fd);


	char *buf;

	char *buf2 = "/";

	char *ruta = malloc(300*sizeof(char));


	if ( strncmp (buffer, "droot", 5 )) {		

		buf = strtok( buffer, "/" );

		buf = strtok( NULL, "\n" );  
	//	printf("\n\%s",buf); 

		strcpy (ruta,buf2);
		strcat(ruta,buf);

	//	printf ("\n buff: %s\n",ruta);


	}

	return ruta;


} // fin funcion ParserRuta
