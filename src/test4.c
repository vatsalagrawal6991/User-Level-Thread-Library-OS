#include <stdio.h>
#include "thread.h"
#include <unistd.h>
mute gh;
int c=0;

void* f1(void* arg){
    int* y=(int*)arg;
    printf("IN THREAD: %d \n",myThreadSelf());
    int n=1000000000;
    while (n--){
        if (n==100||n==100000000){
            get(&gh);
            printf("In CRITICAL SECTION:%d\n",myThreadSelf());
            c=c+1;
            printf("In CRITICAL SECTION c value:%d\n",c);
            printf("OUT CRITICAL SECTION:%d\n",myThreadSelf());
            leave(&gh);
        }
    }
    printf("OUT THREAD: %d\n",myThreadSelf());
}
int main() {
    int th1=10;
    thread* t1[th1];
    int i,n[th1];
    int a =20;
    int* arg1=&a;
    initSem(&gh);
    for (i=0;i<th1;i++){
        n[i] =myThreadCreate(t1[i],NULL,f1,(void*)arg1);
    }
    for (i=0;i<th1;i++){
        myThreadJoin(n[i]);
    }
    return 0;
}