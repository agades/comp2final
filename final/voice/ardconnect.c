#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	//CREACION DE COLA DE MENSAJE SEND PARA ARDUINO
        mqd_t sendqd;
        sendqd = mq_open("/mqsend", O_RDWR);
        if(sendqd < 0){ 
                perror("me_open send");
                return -1; 
        }
        printf("mq_open send  existosa\n");

        //APERTURA DE COLA DE MENSAJE RECEIVE DE ARDUINO
        mqd_t receiveqd;
        receiveqd= mq_open("/mqreceive", O_RDWR);
        if(receiveqd < 0){ 
                perror("me_open receive");
                return -1; 
        }


        char * motor= "motor1";
        if((mq_send(sendqd, motor, strlen(motor), 1)) !=0 ){
    
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
       write(1,ardrespond,strlen(ardrespond));



        return 0;
}
