//
// Created by baadalvm on 17/08/21.
//
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

double Time(){
    const double ms = 1.0e-6;
    struct timeval seco;
    int ss= gettimeofday(&seco, NULL);
    if(ss==-1){
        printf("error");
        return 0;
    }
    double ct = ((double)seco.tv_sec) + (((double)seco.tv_usec))*ms;
    return ct;
}