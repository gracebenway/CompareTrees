//  stack.c
//  Assign0
//
//  Created by Grace Benway on 2/22/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "dll.h"

stack *newStack(void (*d)(FILE *,void *))   //constructor
{
    stack *items = (stack*)malloc(sizeof(stack));
    if (items == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->display = d;
    items->store = newDLL(d);
    return items;
}

void push(stack *items,void *value)         //stores a generic value
{
    insertDLL(items->store, 0, value);
}

void *pop(stack *items)                     //returns a generic value
{
    void *v = removeDLL(items->store, 0);
    return v;
}

void *peekStack(stack *items)               //returns a generic value
{
    void *v = getDLL(items->store, (items->store->size)-1);
    return v;
}

int sizeStack(stack *items)
{
    return items->store->size;
}

void displayStack(FILE *fp,stack *items)
{
    displayDLL(fp, items->store);
}
