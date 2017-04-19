//
//  sll.h
//  Assign0
//
//  Created by Grace Benway on 2/15/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#ifndef sll_h
#define sll_h

#include <stdio.h>

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

typedef struct sllnode {
    struct sllnode *next;
    void *value;
} sllnode;

typedef struct sll
{
    sllnode *head;
    sllnode *tail;
    int size;
    void (*display)(FILE *,void *);
} sll;

extern sllnode *newSLLnode(void *v);
extern sll *newSLL(void (*d)(FILE *,void *));            //constructor
extern sllnode *returnHead(sll *items);
extern sllnode *returnTail(sll *items);
extern int isEmpty(sll *items);
extern void insertSLL(sll *items,int index,void *value); //stores a generic value
extern void *removeSLL(sll *items,int index);            //returns a generic value
extern void unionSLL(sll *recipient,sll *donor);         //merge two lists into one
extern void *getSLL(sll *items,int index);               //get the value at the index
extern int sizeSLL(sll *items);
extern void displaySLL(FILE *,sll *items);

#endif

#endif /* sll_h */
