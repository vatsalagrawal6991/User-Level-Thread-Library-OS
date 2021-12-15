#ifndef THREAD_H
#define THREAD_H

#include <setjmp.h>
#define MythreadArg ((*inCpu).arg);

typedef unsigned long ul;

typedef enum stateofcpu{
    Ready=1,Running=2,Cancelled=4,Finished=5,scheduler=6
}state;

typedef struct threadtcb {
    int tid;
    state st;
    sigjmp_buf context;
    int* sta;
    void* (*func)(void*);
    void* attr;
    void* arg;
}thread;
typedef struct node{
    thread* data;
    struct node* nl;
    struct node* pl;
}nod;
typedef struct ques{
    nod* head;
    nod* tail;
    int len;
}que;
typedef struct sema{
    int lock;
    que* waiting;
}mute;

typedef struct con{
    int lock;
    que* wai;
    que* ri;
}cv;

typedef struct size{
    int ss;
}myThreadAttr;


int myThreadCreate (thread* th,myThreadAttr* attr, void* (*funca)(void*),void* arg);
void myThreadExit(void* ret);
void myThreadCancel(thread* th);
void myThreadAttrInit(myThreadAttr* attr);
void myThreadAttrDestroy(myThreadAttr* attr);
int myThreadSelf();
void myThreadYield();
void myThreadJoin(int tid);
int initSem(mute* t);
int get(mute* t);
int leave(mute* t);
int initCV(cv* t);
int wait(cv* t,mute* s);
int sign(cv* t);
#include "queue.h"
#endif