#include <stdio.h>
#include "thread.h"
#include <unistd.h>
mute gh;
int c=5;
cv gc;

void* f1(void* arg){
    int* y=(int*)arg;
    int x=myThreadSelf();
    printf("IN THREAD: %d \n",myThreadSelf());
    int n=10;
    while (c>0){
                get(&gh);
                while(c==4||c==2){wait(&gc,&gh); }
                printf("In CRITICAL SECTION:%d\n",myThreadSelf());
                printf("In CRITICAL SECTION c value:%d\n",c);
                c--;
                printf("OUT CRITICAL SECTION:%d\n",myThreadSelf());
                leave(&gh);
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
        printf("In CRITICAL SECTION:%d\n",myThreadSelf());
        printf("In CRITICAL SECTION c value:%d\n",c);
        c--;
        printf("OUT CRITICAL SECTION:%d\n",myThreadSelf());
        sign(&gc);
        leave(&gh);
    }
    printf("OUT THREAD: %d\n",myThreadSelf());
}
int main() {
    int th1=1;
    thread* t1[th1];
    thread* t2[th1];
    int i,n1[th1],n2[th1];
    int a =20;
    int* arg1=&a;
    initSem(&gh);
    initCV(&gc);
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

