#include "header.h"

char *recurso (char *buffer, char *archivo, char *tipo, long *longitud, char *ruta)
{

	int leido;
	int fd;

	//char *buffer2 = malloc (80000 * sizeof (char));
	// strcpy (buffer2, buffer);

	char archivoaux[256];		//para parsear la ext
	memset (archivoaux, 0, sizeof archivoaux);

	char archivoaux2[256];		//para calcular la longitud del archivo una ves encontrado
	memset (archivoaux2, 0, sizeof archivoaux2);

	char index[256];		// index.html
	memset (index, 0, sizeof index);

	char *archivo3;

	char *buf = malloc (256 * sizeof (char));	//para nombre
	char *ext = malloc (256 * sizeof (char));	//para extension

	char *nombre = malloc (256 * sizeof (char));	// nombre del archivo

	buf = strtok (buffer, "/");
	//printf("\n1: %s\n",buf);
	buf = strtok (NULL, " ");
	//printf("\n2: %s\n",buf);
	archivo3 = buf;		// almacena nombre del archivo
	//printf("\n3:%s\n",archivo3);

	//apunta a index si no hay parametro
	if ((strncmp (archivo3, "HTTP/1.1", 8)) == 0)
	{

		strncpy (index, "index.html", 10);	//index  solo lo uso para el index.html
		strcpy (archivo3, index);	// copio index.html a archivo3
	}

	printf ("El archivo es: %s\n", archivo3);
	strcpy (nombre, archivo3);
	strcpy (archivoaux, archivo3);	//copia para parsear extension

	ext = strtok (archivoaux, ".");
	ext = strtok (NULL, " ");
	//ext = buf2;

	// tipo de extensiones

	if (strcmp (ext, "html") == 0)
	{
		strncpy (tipo, "text/html", 256);
	}

	if (strcmp (ext, "jpg") == 0)
	{
		strncpy (tipo, "image/jpeg", 256);
	}

	if (strcmp (ext, "pdf") == 0)
	{
		strncpy (tipo, "application/pdf", 256);
	}

	if (strcmp (ext, "txt") == 0)
	{
		strncpy (tipo, "text/plain", 256);
	}

	//ruta completa del archivo
	strcpy (archivoaux, archivo3);	//aux tiene el nombre del archivo

	strncpy (archivo3, ruta, 256);

	strncat (archivo3, archivoaux, 256);

	strcpy (archivo, archivo3);


	if ((fd = open (archivo, O_RDONLY)) != -1)
	{				// si el archivo existe

		while ((leido = read (fd, archivoaux2, sizeof (archivoaux2))) > 0)

			*longitud = *longitud + leido;	//terminar con la longitud del archivo

		close (fd);
	}
	else{
		perror("Error en open 1 recurso.c \n");
	}

	return nombre;

}				// fin funcion
