#include <stdio.h>
#include <malloc.h>
#include <signal.h>
#include "thread.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

void myThreadSwitch();
void contextSwitch();
void cS(int);
void wrap();

static int thcount;
//static int prempt=1;

struct sigaction schfun;
struct itimerval itime;

thread* inCpu,*sch;
que* rdy,* ft;
int empt;

int cas(int* original, int old, int new){
    asm volatile("lock; cmpxchg %2, %0 \n":"+m" (*original), "+a"(old) :"r"(new));
    return old;
}
ul assemVoltaile(ul x){
    ul a;
    asm volatile("xor %%fs:0x30,%0\n""rol $0x11,%0\n": "=g" (a): "0" (x));
    //%%-register, %-input operand"", $-immediate, "="result operand, ""input operand with condition
    // m- memory, g-anything register memory immediate, r-register, = first read then write, : specify operand
    //cc - flags are changed, 0-9 operand matching, volatile-compiler optimization off no code place changing
    return a;
}

int myThreadCreate (thread* th,myThreadAttr* attr, void* (*funca)(void*),void* arg){
    if (thcount==0){
        myThreadSwitch();
    }
    ++thcount;
    th=(thread*)malloc(sizeof(thread));
    th->tid=thcount;
    int ssp;
    if (attr==NULL){
        ssp=4096;
    }
    else{
        ssp=attr->ss;
    }
    th->sta=(int*)malloc(ssp*sizeof(int)); //char because it is byte addresable, jmp is integer array
    th->func=funca;
    th->attr=attr;
    th->arg=arg;
    sigsetjmp(th->context,1);

    (th->context->__jmpbuf)[6]=assemVoltaile((ul)th->sta +ssp-(sizeof (int)));
    (th->context->__jmpbuf)[7]=assemVoltaile((ul)wrap);
    sigemptyset(&th->context->__saved_mask);
        th->st=1;
        pushb(rdy,th);

    return th->tid;
}

void myThreadSwitch(){
    rdy=ini();
    ft=ini();
    empt=0;
    sch=(thread*) malloc(sizeof(thread));
    sch->tid=0;
    sigemptyset(&sch->context->__saved_mask);
    sch->st=6;
    schfun.sa_handler=&cS;
    sigemptyset(&schfun.sa_mask);
    schfun.sa_flags=SA_NODEFER;
    sigaction(SIGVTALRM,&schfun,NULL);
    itime.it_interval.tv_usec=50000;
    itime.it_interval.tv_sec=0;
    itime.it_value.tv_usec=50000;
    itime.it_value.tv_sec=0;
    setitimer(ITIMER_VIRTUAL,&itime,NULL);
    inCpu=sch;
}

void (cS)(int a){
    contextSwitch();
}
void contextSwitch(){
    sigaddset(&schfun.sa_mask,SIGVTALRM);
    if(inCpu->st!=6){
        inCpu->st=1;
    }
    pushb(rdy,inCpu);
    if(sigsetjmp(inCpu->context,1)==1){
        sigemptyset(&schfun.sa_mask);
        return;
    }
    inCpu= front(rdy);
    popf(rdy);
    if(inCpu->st==6){
        if (rdy->len==0){
            empt++;
            if (empt==4){
                 int abc;
                 for(abc=1;abc<=thcount;abc++){
                     free(front(ft));
                     popf(ft);
                 }
                itime.it_interval.tv_usec=0;
                itime.it_interval.tv_sec=0;
                itime.it_value.tv_usec=0;
                itime.it_value.tv_sec=0;
                setitimer(ITIMER_VIRTUAL,&itime,NULL);
                empt=0;
                thcount=0;
                return;
            }

        }
        pushb(rdy,inCpu);
        inCpu= front(rdy);
        popf(rdy);
    }
    inCpu->st=2;
    //setitimer(ITIMER_VIRTUAL,&itime,NULL);
    siglongjmp(inCpu->context,1);
}
void myThreadExit(void* ret){
    sigaddset(&schfun.sa_mask,SIGVTALRM);
    inCpu->st=5;
    pushb(ft,inCpu);
    //*ret=1;
    if (rdy->len==0){

        return  ;
    }
    inCpu= front(rdy);
    inCpu->st=2;
    popf(rdy);
    //setitimer(ITIMER_VIRTUAL,&itime,NULL);
    longjmp(inCpu->context,1);
}
void myThreadCancel(thread* th){
    inCpu->st=4;
    if(th==inCpu){
        int ret=0;
        myThreadExit(&ret);
    }
    if (found(ft,th)==1){
        return;
    }
    if (deleten(rdy,th)==1){
        pushb(ft,th);
    }
    else {printf("not found");}
}
void myThreadAttrInit(myThreadAttr* attr){
    attr=(myThreadAttr*) malloc(sizeof(myThreadAttr));
    attr->ss=4096;
}
void myThreadAttrDestroy(myThreadAttr* attr){
    free(attr);
    attr=NULL;
}
int myThreadSelf(){
    return inCpu->tid;
}
void myThreadYield(){
    contextSwitch();
}
void myThreadJoin(int tid){
    while(1){
        if(findtidnc(ft,tid)==1){
            break;
        }
    }
    return;
}
int initSem(mute* t){
    //t=(mute*) malloc(sizeof(mute));
    t->lock=0;
    t->waiting= ini();
    return 1;
}
int get(mute* t){
    pushb(t->waiting,inCpu);
    while (((t->waiting->head->data)!=inCpu)||(cas(&(t->lock),0,1)!=0)){
      contextSwitch();
    };
    return 1;
}
int leave(mute* t){
    t->lock=0;
    popf(t->waiting);
    return 1;
}
int initCV(cv* t){
    t->ri=ini();
    t->wai=ini();
    t->lock=0;
    return 1;
}
int wait(cv* t,mute* s){
    if(s!=NULL){
        pushb(t->wai,inCpu);
        leave(s);
        while(t->ri->len==0||t->ri->head->data!=inCpu){
            contextSwitch();
        }
        popf(t->ri);
        get(s);
    }
    else{
        pushb(t->wai,inCpu);
        while(t->ri->head->data!=inCpu){
            contextSwitch();
        }
        popf(t->ri);
    }
    return 1;
}
int sign(cv* t){
    thread* t1=front(t->wai);
    if(t1!=NULL){
        pushb(t->ri,t1);
    }
    popf(t->wai);
    return 1;
}

void wrap(){
    (inCpu->func)(inCpu->arg);
    int a=10;
    myThreadExit(&a);
}