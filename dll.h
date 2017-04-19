//
//  dll.h
//  Assign0
//
//  Created by Grace Benway on 2/15/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#ifndef dll_h
#define dll_h

#include <stdio.h>

typedef struct dllnode {
    struct dllnode *next;
    struct dllnode *previous;
    void *value;
} dllnode;

typedef struct dll {
    dllnode *head;
    dllnode *tail;
    int size;
    void (*display)(FILE *,void *);
} dll;

extern dllnode *newDLLnode(void *v);
extern dll *newDLL(void (*d)(FILE *,void *));            //constructor
extern int isDEmpty(dll *items);
extern void insertDLL(dll *items,int index,void *value); //stores a generic value
extern void *removeDLL(dll *items,int index);            //returns a generic value
extern void unionDLL(dll *recipient,dll *donor);         //merge two lists into one
extern void *getDLL(dll *items,int index);               //get the value at the index
extern int sizeDLL(dll *items);
extern void displayDLL(FILE *,dll *items);

#endif /* dll_h */
