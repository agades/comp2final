#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "arduino-serial-lib.c"
#include "arduino-serial-lib.h"

int main(){
//variables de cola de mensaje send	

	if(((mq_unlink("/mqsend"))==0)){
	printf("eliminacion exitosa mqsend \n");
	}
	if(((mq_unlink("/mqreceive"))==0)){
	printf("eliminacion exitosa mqreceive \n");
      	}

	mqd_t qdsend;
	char mensaje[8192];
	int leido;
	unsigned int prio;
	struct mq_attr atri;
	qdsend= mq_open("/mqsend", O_RDWR|O_CREAT, 0664,NULL);
//variables de cola de mensaje receive
	 mqd_t qdreceive;
	 qdreceive = mq_open("/mqreceive", O_RDWR|O_CREAT, 0664,NULL);	
	 if(qdreceive < 0){ 
                perror("me_open");
                return -1; 
        }
        printf("mq_open receive  existosa\n");
	printf("esperando orden\n");

//variables de arduino
	char ardrespond[100];
        char eolchar = '\n';
	int dev = serialport_init("/dev/ttyACM0", 9600); //abrimos puerto serie arduino	

	if(qdsend < 0){
		perror("me_open");
		return -1;
	}
	mq_getattr(qdsend, &atri);
	if(mq_getattr(qdsend, &atri)< 0){
		perror("mq_attr");
		return -1;
	}
	//printf("mq_open existosa\n");
	
	while((leido = mq_receive(qdsend, mensaje, atri.mq_msgsize, &prio))>0){
	if(leido < 0){
		perror("mq_receive");
		return -1;
	}
	

	printf("%d bytes leidos, prioridad %d, centenido: %s \n", leido, prio, mensaje);

	if((strcmp(mensaje,"motor1"))==0){
                 serialport_write(dev, "1");
                 serialport_read_until(dev, ardrespond, eolchar, 256, 5000);
                 printf("Enviando respuesta : %s\n", ardrespond);
	        if((mq_send(qdreceive, ardrespond, strlen(ardrespond),1)) !=0 ){
    
                perror("mq_send qdreceive ");
                return -1; 
        }


}
	
	printf("esperando orden\n");
}
	return 0;
}
