//
//  vbst.c
//  Assign3
//
//  Created by Grace Benway on 4/3/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "vbst.h"

typedef struct vbstValue
{
    void *value;
    int freq;
    void (*display)(FILE *,void *);
    int (*compare)(void *,void *);
}vbstValue;

vbstValue *newVBSTvalue(vbst *b, void *v)
{
    vbstValue *n = (vbstValue*)malloc(sizeof(vbstValue));
    n->value = v;
    n->compare = b->compare;
    n->display = b->display;
    n->freq = 1;
    return n;
}

int vbstCompare(void *p,void *q)
{
    vbstValue *c = p;
    vbstValue *d = q;
    return c->compare(c->value,d->value);
}

void vbstValueDisplay(FILE *fp,void *v)
{
    vbstValue *temp = v;
    temp->display(fp,temp->value);
    if (temp->freq > 1)
        fprintf(fp,"-%d",temp->freq);
}

vbst *newVBST(void (*d)(FILE *,void *),int (*c)(void *,void *))
{
    vbst *new = (vbst*)malloc(sizeof(vbst));
    if (new == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    new->tree = newBST(vbstValueDisplay,vbstCompare);
    new->display = d;
    new->compare = c;
    new->size = 0;
    new->words = 0;
    return new;
}

void insertVBST(vbst *b,void *v)
{
    vbstValue *newV = newVBSTvalue(b,v);
    bstNode *n = findBSTNode(b->tree,newV);
    if (n == NULL)
        insertBST(b->tree,newV);
    else
    {
        vbstValue *w = n->value;
        w->freq++;
    }
    b->words++;
}

int getFreqV(vbst *b,void *v)
{
    if (findVBST(b,v) == 1)
    {
        vbstValue *w = v;
        return w->freq;
    }
    return 0;
}

int findVBST(vbst *b,void *v) //for freq;
{
    vbstValue *newV = newVBSTvalue(b,v);
    bstNode *found = findBSTNode(b->tree,newV);
    if (found != 0)
    {
        vbstValue *temp = found->value;
        fprintf(stdout,"%i",temp->freq);
    }
    return 0;
}

void deleteVBST(vbst *b,void *v)
{
    vbstValue *temp = newVBSTvalue(b,v);
    bstNode *found = findBSTNode(b->tree,temp);
    if (found != NULL)
    {
        vbstValue *w = found->value;
        if (w->freq > 1)
            w->freq--;
        else
        {
            found = swapToLeafBSTNode(found);
            pruneBSTNode(b->tree,found);
        }
    }else
    {
        fprintf(stderr,"Value ");
        b->display(stderr,temp->value);
        fprintf(stderr," not found");
    }
    b->words--;
}

int sizeVBST(vbst *b)
{
    return b->tree->size;
}

int wordsVBST(vbst *b)
{
    return b->words;
}

void statisticsVBST(vbst *b,FILE *fp)
{
    fprintf(fp,"Words/Phrases: %i\n", wordsVBST(b));
    statisticsBST(b->tree,fp);
}

void displayVBST(FILE *fp,vbst *b)
{
    displayBST(fp,b->tree);
}
