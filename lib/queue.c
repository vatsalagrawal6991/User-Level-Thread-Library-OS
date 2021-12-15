#include "queue.h"
#include <stdio.h>
#include <malloc.h>

que* ini (){
    que* t = (que*)malloc(sizeof(que));
    t->head=NULL;
    t->tail=NULL;
    t->len=0;
    return t;
}
void pushf(que* t, thread* n){
    nod* new= (nod*)malloc(sizeof(nod));
    if(t->len==0){
        t->head=new;
        t->tail=new;
        new->nl=NULL;
        new->pl=NULL;
    }
    else{
        new->nl=t->head;
        new->pl=NULL;
        t->head->pl=new;
        t->head=new;
    }
    (t->len)++;
    new->data=n;
}
void pushb(que* t, thread* n){
    nod* new= (nod*)malloc(sizeof(nod));
    if(t->len==0){
        t->head=new;
        t->tail=new;
        new->nl=NULL;
        new->pl=NULL;
    }
    else{
        new->pl=t->tail;
        new->nl=NULL;
        t->tail->nl=new;
        t->tail=new;
    }
    (t->len)++;
    new->data=n;
}
int popb(que* t){
    nod* pop;
    if(t->len==0){
        return -1;
    }
    pop=t->tail;
    if(t->len==1){
        t->head=NULL;
        t->tail=NULL;
        free(pop);
        (t->len)--;
        return 1;
    }
    t->tail=pop->pl;
    t->tail->nl=NULL;
    free(pop);
    (t->len)--;
    return 1;
}
int popf(que* t){
    nod* pop;
    if(t->len==0){
        return -1;
    }
    pop=t->head;
    if(t->len==1){
        t->head=NULL;
        t->tail=NULL;
        free(pop);
        (t->len)--;
        return 1;
    }
    t->head=pop->nl;
    t->head->pl=NULL;
    free(pop);
    (t->len)--;
    return 1;
}
thread* front(que* t){
    if(t->len==0){
        return NULL;
    }
    return t->head->data;
}
thread* back(que* t){
    if(t->len==0){
        return NULL;
    }
    return t->tail->data;
}
int found(que* t,thread* th){
    nod* h=t->head;
    if (h->data==th){
        return 1;}
    while(h->nl!=NULL){
        h=h->nl;
        if (h->data==th){
            return 1;
        }
    }
    return 0;
}
int deleten(que* t,thread* th){
    nod* h=t->head;
    if (h->data==th){
        popf(t);
        return 1;
    }
    while(h->nl!=NULL){
        h=h->nl;
        if (h->data==th){
            nod* h1=h->pl;
            h1->nl=h->nl;
            h1=h->nl;
            h1->pl=h->pl;
            return 1;
        }
    }
    return 0;
}
int findtidnc(que* ft, int tid){
    nod* h=ft->head;
    if(h==NULL){
        return 0;
    }
    if (h->data->tid==tid){
        return 1;
    }
    while(h->nl!=NULL){
        h=h->nl;
        if (h->data->tid==tid){
            return 1;
        }
    }
    return 0;
}