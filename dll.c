//
//  dll.c
//  Assign0
//
//  Created by Grace Benway on 2/15/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

dllnode *newDLLnode(void *v)
{
    dllnode *new = (dllnode*)malloc(sizeof(dllnode));
    new->value = v;
    new->next = 0;
    new->previous = 0;
    return new;
}

dll *newDLL(void (*d)(FILE *,void *))            //constructor
{
    dll *items = (dll*)malloc(sizeof(dll));
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

int isDEmpty(dll *items)
{
    return (items->head == items->tail && items->head == NULL);
}

void insertDLL(dll *items,int index,void *value) //stores a generic value
{
    dllnode *n = newDLLnode(value);
    dllnode *ptr, *temp;
    int i;
    if (isDEmpty(items) && index == 0)
    {
        items->head = n;
        items->tail = n;
        items->size++;
    }
    else if (!isDEmpty(items) && index == 0)
    {
        items->head->previous = n;
        n->next = items->head;
        items->head = n;
        items->size++;
    }
    else if (!isDEmpty(items) && index == sizeDLL(items))
    {
        items->tail->next = n;
        n->previous = items->tail;
        items->tail = n;
        items->size++;
    }
    else
    {
        int a = (items->size) / 2;
        int count = 0;
        if (index > a)
        {
            ptr = items->tail;
            temp = ptr;
            while (count < (items->size - index))
            {
                temp = ptr;
                ptr = ptr->previous;
                count++;
            }
            n->next = temp;
            n->next->previous = n;
            n->previous = ptr;
            n->previous->next = n;
            items->size++;
            
        }
        else
        {
            ptr = items->head;
            temp = ptr;
            for(i = 1; i <= index; i++)
            {
                temp = ptr;
                ptr = ptr->next;
            }
            n->previous = temp;
            n->next = temp->next;
            temp->next->previous = n;
            temp->next = n;
            items->size++;
        }
    }
}

void *removeDLL(dll *items,int index)            //returns a generic value
{
    assert((items->head)!=0);
    int i;
    dllnode *temp = 0;
    dllnode *ptr = 0;
    void *v;
    if (index == 0) //removing head
    {
        temp = items->head;
        items->head = items->head->next;
        if (items->head == 0)
        {
            items->tail = 0;
        }
        else
        {
            items->head->previous = 0;
            //if(items->head->next != 0)
            //    items->head->next->previous = items->head;
            //else
            //    items->tail = items->head;
        }
        v = temp->value;
        items->size--;
        return v;
    }
    else if (index == (sizeDLL(items)-1)) //removing tail
    {
        temp = items->tail;
        items->tail = items->tail->previous;
        items->tail->next = 0;
        v = temp->value;
        items->size--;
        return v;
    }
    else //removing item in middle of list
    {
        ptr = items->head;
        temp = ptr;
        for(i = 0; i < index; i++)
        {
            temp = ptr;
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        ptr->next->previous = temp;
        v = ptr->value;
        items->size--;
        return v;
    }
}

void unionDLL(dll *recipient,dll *donor)         //merge two lists into one
{
    dllnode *t2;
    if (isDEmpty(recipient) && !isDEmpty(donor))
    {
        recipient->head = donor->head;
        recipient->tail = donor->tail;
        recipient->size = donor->size;
    }
    else if(!isDEmpty(donor))
    {
        t2 = donor->head;
        t2->previous = recipient->tail;
        recipient->tail->next = t2;
        recipient->tail = donor->tail;
        recipient->size += donor->size;
    }
    donor->head = donor->tail = 0;
    donor->size = 0;
}

void *getDLL(dll *items,int index)               //get the value at the index
{
    if (isDEmpty(items))
        return 0;
    else
    {
        dllnode *ptr;
        ptr = items->head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
        return ptr->value;
    }
}

int sizeDLL(dll *items)
{
    return items->size;
}

void displayDLL(FILE *fp,dll *items)
{
    dllnode *ptr;
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

