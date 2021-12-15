#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matrixorig.h"

int n;
int **m;
int **a;
int **b;
int x;
int numt;

int main(int argc,char **argv ){
    n=512;
    x=0;
    numt=40;
    if (argc==2){
        n=atoi(argv[1]);
    }
    if (argc==3){
        n=atoi(argv[1]);
        numt=atoi(argv[2]);
    }
    int i,j;

    double avg,avg1,avg2;
    m = (int **)malloc(n*(sizeof(int*)));
    a = (int **)malloc(n*(sizeof(int*)));
    b = (int **)malloc(n*(sizeof(int*)));
    for (i=0;i<n;i++){
        m[i]=(int *)calloc(n,sizeof(int));
        a[i]=(int *)calloc(n,sizeof(int));
        b[i]=(int *)calloc(n,sizeof(int));
    }
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            a[i][j]= rand()%10;
            b[i][j]= rand()%10;
        }
    }
    for(x=numt;x>0;x--){
        //n=2;
        double start = Time();
        matrixorig();
        double stop = Time();
        double tc =stop-start;
        avg=tc/1;
        //printMatrix(m,n);
        //printf("\n");
        thread* t1[x];
        int azx[x];

        double start1 = Time();
        for (i=0;i<x;i++){
            azx[i]=myThreadCreate(t1[i],NULL,matrix,(void*)(&i));
        }
        for (i=0;i<x;i++){
            myThreadJoin(azx[i]);
        }
        double stop1 = Time();
        double tc1 =stop1-start1;
        avg1=(tc1-tc)/(((int)(tc1/0.05))+1);
        //printMatrix(m,n);
        //printf("\n");
        pthread_t th1[x];
        pthread_attr_t atc;
        pthread_attr_init(&atc);
        pthread_attr_setschedpolicy(&atc,SCHED_FIFO);
        double start2 = Time();
        for (i=0;i<x;i++){
            pthread_create(&(th1[i]),NULL,matrix,(void*)&i);
        }
        for (i=0;i<x;i++){
            pthread_join(th1[i],NULL);
        }
        double stop2 = Time();
        double tc2 =stop2-start2;
        avg2=(tc2-tc)/(x);
        //printMatrix(m,n);

        printf("matrix    Thread     Original      MyThread      Pthread\n");
        printf("%d        %d         %lf      %lf      %lf\n",n,x,avg,tc1,tc2);


        //printMatrix(m,n);matrixBlock(mm,a,b,n,bb);
    }
    printf("\n");
    //printf("matrix    Thread       CS MyThread      CS Pthread\n");
    //printf("%d        %d             %lf      %lf\n",n,++x,avg1,avg2);
    printf("\n");
    x=16;
    n=128;
    //for (n=2;n<=512;n=n*2){
    //for(x=1;x<41&&x<=n;x++){
        double start = Time();
        matrixorig();
        double stop = Time();
        double tc =stop-start;
        avg=tc/1;
        //printMatrix(m,n);
        //printf("\n");
        thread* t1[x];
        int azx[x];

        double start1 = Time();
        for (i=0;i<x;i++){
            azx[i]=myThreadCreate(t1[i],NULL,matrix,(void*)(&i));
        }
        for (i=0;i<x;i++){
            myThreadJoin(azx[i]);
        }
        double stop1 = Time();
        double tc1 =stop1-start1;
        avg1=(tc1-tc)/(((int)(tc1/0.05))+1);
        //printMatrix(m,n);
        //printf("\n");
/*
    pthrs.sa_handler=&pty;
    sigemptyset(&pthrs.sa_mask);
    pthrs.sa_flags=SA_NODEFER;
    sigaction(SIGVTALRM,&pthrs,NULL);
    ptim.it_interval.tv_usec=50000;
    ptim.it_interval.tv_sec=0;
    ptim.it_value.tv_usec=50000;
    ptim.it_value.tv_sec=0;
    setitimer(ITIMER_VIRTUAL,&ptim,NULL);*/
        pthread_t th1[x];
        pthread_attr_t atc;
        pthread_attr_init(&atc);
        pthread_attr_setschedpolicy(&atc,SCHED_FIFO);
        double start2 = Time();
        for (i=0;i<x;i++){
            pthread_create(&(th1[i]),NULL,matrix,(void*)&i);
        }
        for (i=0;i<x;i++){
            pthread_join(th1[i],NULL);
        }
        double stop2 = Time();
        double tc2 =stop2-start2;
        avg2=(tc2-tc)/(x);
        //printMatrix(m,n);

        //printf("matrix    Thread     Original      MyThread      Pthread\n");
        //printf("%d        %d         %lf      %lf      %lf\n",n,x,avg,tc1,tc2);
        printf("matrix    Thread      Average CS MyThread      Average CS Pthread\n");
        printf("%d        %d          %lf                      %lf\n",n,x,avg1,avg2);
    printf("negative value denotes parallel processing\n");
        //printMatrix(m,n);matrixBlock(mm,a,b,n,bb);
    //}}


    //printMatrix(a,n);
    //printMatrix(b,n);
    //printf("%d",i);
    //fflush(stdout);
        for (i=0;i<n/2;i++){
            free(m[i]);
            free(a[i]);
            free(b[i]);
        }
        free(m);
        free(a);
        free(b);
}
