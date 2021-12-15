#include <stdio.h>
#include "thread.h"
#include <unistd.h>

void* f1(void* arg){
    int* y=(int*)arg;
    printf("IN THREAD: %d \n",myThreadSelf());
    int n=1000000;
    while (n--){
        if (n==100){
            printf("I AM GOING TO Yield :%d\n",myThreadSelf());
            myThreadYield();
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
    for (i=0;i<th1;i++){
        n[i] =myThreadCreate(t1[i],NULL,f1,(void*)arg1);
    }
    for (i=0;i<th1;i++){
        myThreadJoin(n[i]);
    }
    return 0;
}