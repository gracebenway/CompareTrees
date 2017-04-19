//
//  queue.c
//  Assign0
//
//  Created by Grace Benway on 2/22/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sll.h"


queue *newQueue(void (*d)(FILE *,void *))   //constructor
{
    queue *items = (queue*)malloc(sizeof(queue));
    if (items == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->display = d;
    items->store = newSLL(d);
    return items;
}

void enqueue(queue *items,void *value)      //stores a generic value
{
    insertSLL(items->store, items->store->size, value);
}

void *dequeue(queue *items)                 //returns a generic value
{
    void *v = removeSLL(items->store, 0);
    return v;
}

void *peekQueue(queue *items)               //returns a generic value
{
    void *v = getSLL(items->store, 0);
    return v;
}

int sizeQueue(queue *items)
{
    return items->store->size;
}

void displayQueue(FILE *fp,queue *items)
{
    displaySLL(fp, items->store);
}
