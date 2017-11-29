#include "header.h"
// #include "arduino-serial-lib.c"
//#include "arduino-serial-lib.h"

char *http_worker (int acceptfd, char *ruta,mqd_t sendqd,mqd_t receiveqd)
{

	int fd;
	int leido;
	int leido3;

	//para recurso
	long longitud = 0;
	char archivo[256];
	char tipo[256];

	//para reponse
	char *estado;
	char cabecera[256];
	char *version = "HTTP/1.1";

	char buffer[8000];		//request
	memset (buffer, 0, sizeof buffer);

	char buffer2[800];
	memset (buffer2, 0, sizeof buffer2);


	char *nombre = malloc (256 * sizeof (char));

	if((leido = read (acceptfd, buffer, sizeof (buffer))) > 0)
	{
	//	printf("recibi del navegador : %s \n",buffer); 
		memset (tipo, 0, sizeof tipo);
		memset (archivo, 0, sizeof archivo);

		nombre = recurso (buffer, archivo, tipo, &longitud, ruta);
	//	printf("la variable nombre es %s \n",nombre);

		if (!(strncmp (buffer, "GET", 3) == 0))
		{
			estado = "HTTP/1.1 500 INTERNAL SERVER ERROR\n\nInternal Server error\n";
			if(write (acceptfd, estado, strlen (estado))<0){
			perror("erorr en write 1 de  http_worker\n");
			//exit (0);
			return 0;
		}

		}


		if ((fd = open (archivo, O_RDONLY)) < 0)
		{	perror("error");
			estado = "HTTP/1.1 404 NOT FOUND\n\nno esta el archivo\n";
			if(write (acceptfd, estado, strlen (estado))<0){
			perror("Error en write 2 http_worker \n");
			//close (fd);
		return 0;
			}

		}
		else
		{
			estado = "200 OK";
			leido3 =
				snprintf (cabecera, sizeof cabecera,
						"%s %s\nContent-Type: %s\n\n",
						version, estado, tipo);
					//	"%s %s\nContent-Length: %ld\nContent-Type: %s\n\n",
					//	version, estado, longitud, tipo);
			if(write (acceptfd, cabecera, leido3)<0){
				perror("Error en write 3 http_worker \n");
			}
			while ((leido3 = read (fd, buffer2, sizeof buffer2)) > 0)
			{

				if(write (acceptfd, buffer2, leido3)<0){
				perror("Error en write 4 http_worker \n");
				}
				memset (buffer2, 0, sizeof buffer2);
			}

			close (fd);



		}
}					// fin if leido

	//LLAMADA A LA FUNCION ARD
	if((strcmp(nombre,"motor.html"))==0){
	int ard;
	if((ard=ardconnect(acceptfd,sendqd,receiveqd))<0){
	perror("error en ardconnect");
	}

}

//}

	return nombre;

}				// fin funcion
