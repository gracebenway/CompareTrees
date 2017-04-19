//
//  sll.c
//  Assign0
//
//  Created by Grace Benway on 2/15/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include "sll.h"


sllnode *newSLLnode(void *v)
{
    sllnode *new = (sllnode*)malloc(sizeof(sllnode));
    new->value = v;
    new->next = NULL;
    return new;
}

sll *newSLL(void (*d)(FILE *,void *)) //constructor; d is the display function
{
    sll *items = (sll*)malloc(sizeof(sll));
    if (items == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

sllnode *returnHead(sll *items)
{
    return items->head;
}

sllnode *returnTail(sll *items)
{
    return items->tail;
}

int isEmpty(sll *items)
{
    return (items->head == items->tail && items->head == NULL);
}

void insertSLL(sll *items,int index,void *value) //stores a generic value
{
    sllnode *n = newSLLnode(value);
    sllnode *temp, *ptr;
    int i;
    if (isEmpty(items))  //inserting at head and empty
    {
        items->head = n;
        items->tail = n;
        items->size++;
    }
    else if (index == 0) //inserting at head and not empty
    {
        n->next = items->head;
        items->head = n;
        items->size++;
    }
    else if (index == sizeSLL(items)) //inserting at tail and not empty
    {
        items->tail->next = n;
        items->tail = n;
        items->size++;
    }
    else //inserting in middle
    {
        ptr = items->head;
        temp = ptr;
        for(i = 1; i <= index; i++)
        {
            temp = ptr;
            ptr = ptr->next;
        }
        n->next = temp->next;
        temp->next = n;
        items->size++;
    }
}

void *removeSLL(sll *items,int index)            //returns a generic value
{
    assert((items->head)!=0);
    int i;
    sllnode *temp = 0;
    sllnode *ptr = 0;
    void *v;
    if (index == 0) //removing head
    {
        ptr = items->head;
        if (items->size > 1)
        {
            items->head = items->head->next;
        }
        else
        {
            items->head = 0;
            items->tail = 0;
        }
        v = ptr->value;
        items->size--;
        return v;
    }
    else //removing item in middle of list //interior and tail
    {
        ptr = items->head;
        temp = ptr;
        for(i = 0; i < index; i++)
        {
            temp = ptr;
            ptr = ptr->next;
        }
        if (ptr->next == 0)
            items->tail = temp;
        temp->next = ptr->next;
        v = ptr->value;
        items->size--;
        return v;
    }
}

void unionSLL(sll *recipient,sll *donor)         //merge two lists into one
{
    if (isEmpty(recipient) && !isEmpty(donor))
    {
        recipient->head = donor->head;
        recipient->tail = donor->tail;
        recipient->size = donor->size;
    }
    else if (!isEmpty(donor))
    {
        recipient->tail->next = donor->head;
        recipient->tail = donor->tail;
        recipient->size += donor->size;
    }
    donor->size = 0;
    donor->head = donor->tail = 0;
}

void *getSLL(sll *items,int index)               //get the value at the index
{
    if (isEmpty(items))
        return 0;
    else
    {
        sllnode *ptr;
        ptr = items->head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
        return ptr->value;
    }
}

int sizeSLL(sll *items)
{
    if (isEmpty(items))
        return 0;
    else
        return items->size;
}

void displaySLL(FILE *fp,sll *items)
{
    sllnode *ptr;
    int count = 0;
    ptr = items->head;
    if(ptr != 0)
    {
        while(ptr != 0)
        {
            if(count == 0)
                fprintf(fp,"%s","[");
            items->display(fp,ptr->value);
            if(ptr->next != 0)
                fprintf(fp,"%s",",");
            else
                fprintf(fp,"%s","]");
            ptr = ptr->next;
            count++;
        }
    }
    else
        fprintf(fp,"%s","[]");
}
