#include <stdio.h>
#include "thread.h"
#include <unistd.h>
mute gh;
int c=20;
cv gc,gd;

void* f1(void* arg){
    int* y=(int*)arg;
    int x=myThreadSelf();
    printf("IN THREAD: %d \n",myThreadSelf());
    int n=10;
    while (c>0){
        get(&gh);
        while(c%2!=0){wait(&gc,&gh); }
        printf("In CRITICAL SECTION:%d\n",myThreadSelf());
        printf("In CRITICAL SECTION c value:%d\n",c);
        c--;
        printf("OUT CRITICAL SECTION:%d\n",myThreadSelf());
        sign(&gd);
        leave(&gh);
        myThreadYield();
    }
    printf("OUT THREAD: %d\n",myThreadSelf());
}
void* f2(void* arg){
    int* y=(int*)arg;
    int x=myThreadSelf();
    printf("IN THREAD: %d \n",myThreadSelf());
    int n=10;
    while (c>0){
        get(&gh);
        while(c%2==0){wait(&gd,&gh); }
        printf("In CRITICAL SECTION:%d\n",myThreadSelf());
        printf("In CRITICAL SECTION c value:%d\n",c);
        c--;
        printf("OUT CRITICAL SECTION:%d\n",myThreadSelf());
        sign(&gc);
        leave(&gh);
        myThreadYield();
    }
    printf("OUT THREAD: %d\n",myThreadSelf());
}
int main() {
    int th1=5;
    thread* t1[th1];
    thread* t2[th1];
    int i,n1[th1],n2[th1];
    int a =20;
    int* arg1=&a;
    initSem(&gh);
    initCV(&gc);
    initCV(&gd);
    for (i=0;i<th1;i++){
        n1[i] =myThreadCreate(t1[i],NULL,f1,(void*)arg1);
        n2[i] =myThreadCreate(t2[i],NULL,f2,(void*)arg1);
    }
    for (i=0;i<th1;i++){
        myThreadJoin(n1[i]);
        myThreadJoin(n2[i]);
    }
    return 0;
}

