//
//  stack.h
//  Assign0
//
//  Created by Grace Benway on 2/22/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include "dll.h"

typedef struct stack
{
    dll *store;
    void (*display)(FILE *,void *);
} stack;

extern stack *newStack(void (*d)(FILE *,void *));   //constructor
extern void push(stack *items,void *value);         //stores a generic value
extern void *pop(stack *items);                     //returns a generic value
extern void *peekStack(stack *items);               //returns a generic value
extern int sizeStack(stack *items);
extern void displayStack(FILE *,stack *items);

#endif /* stack_h */
