#include <stdio.h>
#include "thread.h"
#include <unistd.h>
#include <stdlib.h>

int produced;
int consumed;
int conta;
int prod;
int consu;
int max;
cv f;
cv nf;
mute bu;


void produce(){
    while(1){
    get(&bu);
    while(conta==max){
        wait(&f,&bu);
       
    }
        printf("Acquired  Container by Producer %d\n",(myThreadSelf()+1)/2);
       if (produced<(10*max)){
    produced++;
    conta++;
    	printf("Produced Container %d\n",produced);}
        printf("Deposited Container by Producer %d\n",(myThreadSelf()+1)/2);
         if ((produced>=(10*max))||(consumed>=(10*max))){
            int ret;
             sign(&nf);
    		leave(&bu);
            myThreadExit(&ret);
        }
    sign(&nf);
    leave(&bu);
    //myThreadYield();
    }

}
void consume(){
    while(1){
    get(&bu);
    while(conta==0){
        wait(&nf,&bu);
        
    }
        printf("Acquired  Container by Consumer %d\n",myThreadSelf()/2);
        if (consumed<(10*max)){
    consumed++;
    conta--;
    	printf("Consumed Container %d\n",consumed);}
        printf("Deposited Container by Consumer %d\n",myThreadSelf()/2);
        if ((produced>=(10*max))||(consumed>=(10*max))){
        int ret;
        sign(&f);
        leave(&bu);
        myThreadExit(&ret);
    }
    sign(&f);
    leave(&bu);
    //myThreadYield();
}}

int main(int argc,char **argv){
    produced=0;
    consumed=0;
    conta=0;
    prod=20;
    consu=20;
    max=200;
    if (argc==3){
        prod=atoi(argv[1]);
        consu=atoi(argv[1]);
        max=atoi(argv[2]);
    }
    initCV(&nf);
    initCV(&f);
    initSem(&bu);
    int i=0;
    thread* t1[prod];
    thread* t2[consu];
    int azx1[prod], azx2[consu];
    for (i=0;i<prod;i++){
        azx1[i]=myThreadCreate(t1[i],NULL,produce,NULL);
        azx2[i]=myThreadCreate(t2[i],NULL,consume,NULL);
    }
    for (i=0;i<consu;i++){
        myThreadJoin(azx1[i]);
        myThreadJoin(azx2[i]);
    }
    return 0;
}
