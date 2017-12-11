#include "header.h"
int ardconnect(int acceptfd,mqd_t sendqd,mqd_t receiveqd,char * orden){

	//ENVIO A LA COLA DE MENSAJE SEND LA ORDEN
	//char * motor= "motor1";
	if((mq_send(sendqd, orden, strlen(orden), 1)) !=0 ){

		perror("mq_send");
		return -1;  

	}   
	printf("mq_send existosa\n");

	//RECIBO DE COLA DE MESAJE RECEIVE LA RESPUESTA      
	char ardrespond[8192];
	int ardleido;
	unsigned int prio;
	struct mq_attr atri;
	mq_getattr(receiveqd, &atri);
	if(mq_getattr(receiveqd, &atri)< 0){ 
		perror("mq_attr");
		return -1;  
	}

	ardleido = mq_receive(receiveqd, ardrespond, atri.mq_msgsize, &prio); 
	if(ardleido < 0){ 
		perror("mq_receive");
		return -1;
	}

	printf("%d bytes leidos, prioridad %d, centenido: %s \n", ardleido, prio, ardrespond);
	write(acceptfd,ardrespond,strlen(ardrespond));

	return 0;
}
