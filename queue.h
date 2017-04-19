//
//  queue.h
//  Assign0
//
//  Created by Grace Benway on 2/22/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "sll.h"

typedef struct queue
{
    sll *store;
    void (*display)(FILE *,void *);
} queue;

extern queue *newQueue(void (*d)(FILE *,void *));   //constructor
extern void enqueue(queue *items,void *value);      //stores a generic value
extern void *dequeue(queue *items);                 //returns a generic value
extern void *peekQueue(queue *items);               //returns a generic value
extern int sizeQueue(queue *items);
extern void displayQueue(FILE *fp,queue *items);

#endif /* queue_h */
