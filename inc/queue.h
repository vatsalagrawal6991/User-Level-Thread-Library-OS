#ifndef QUEUE_H
#define QUEUE_H
#include "thread.h"

que* ini ();
void pushf(que* t, thread* n);
void pushb(que* t, thread* n);
int popb(que* t);
int popf(que* t);
thread* front(que* t);
thread* back(que* t);
int found(que* t,thread* th);
int deleten(que* t,thread* th);
int findtidnc(que* ft, int tid);

#endif