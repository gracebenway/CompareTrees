//
//  rbt.c
//  Assign3
//
//  Created by Grace Benway on 4/6/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "vbst.h"

#define RED 0
#define BLACK 1

typedef struct rbtValue
{
    void *value;
    int freq;
    int color;
    void (*display)(FILE *,void *);
    int (*compare)(void *,void *);
}rbtValue;

rbtValue *newRBTvalue(rbt *b, void *v)
{
    rbtValue *n = (rbtValue*)malloc(sizeof(rbtValue));
    n->value = v;
    n->compare = b->compare;
    n->display = b->display;
    n->color = RED;
    n->freq = 1;
    return n;
}

int rbtCompare(void *p,void *q)
{
    rbtValue *c = p;
    rbtValue *d = q;
    return c->compare(c->value,d->value);
}

void rbtValueDisplay(FILE *fp,void *v)
{
    rbtValue *temp = v;
    temp->display(fp,temp->value);
    if (temp->freq > 1)
        fprintf(fp,"-%d",temp->freq);
    if (temp->color == 0)
        fprintf(fp,"-%s","R");
    else
        fprintf(fp,"-%s","B");
}

rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *))
{
    rbt *new = (rbt*)malloc(sizeof(rbt));
    if (new == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    new->tree = newBST(rbtValueDisplay,rbtCompare);
    new->display = d;
    new->compare = c;
    new->size = 0;
    new->words = 0;
    return new;
}

void leftRotate(rbt *b,bstNode *x)
{
    bstNode *par = x->parent;
    bstNode *grandPar = par->parent;
    x->parent = grandPar;
    par->right = x->left;
    par->parent = x;
    x->left = par;
    if(par->right != NULL)
        par->right->parent = par;
    if (grandPar == par)
    {
        b->tree->root = x;
        x->parent = x;
    }else if (grandPar->left == par)
        grandPar->left = x;
    else
        grandPar->right = x;
}

void rightRotate(rbt *b,bstNode *x)
{
    bstNode *par = x->parent;
    bstNode *grandPar = par->parent;
    x->parent = grandPar;
    par->left = x->right;
    par->parent = x;
    x->right = par;
    if(par->left != NULL)
        par->left->parent = par;
    if (grandPar == par)
    {
        b->tree->root = x;
        x->parent = x;
    }else if (grandPar->left == par)
        grandPar->left = x;
    else
        grandPar->right = x;
}

int getColor(bstNode *n)
{
    if (n == NULL)
        return 1;
    else
    {
        rbtValue *v = n->value;
        return v->color;
    }
}

int isLeftChild(bstNode *n)
{
    if (n->parent->left == n)
        return 1;
    return 0;
}

bstNode *uncle(bstNode *n)
{
    if (isLeftChild(n->parent) == 1)
        return n->parent->parent->right;
    else
        return n->parent->parent->left;
}

void changeColor(bstNode *n,int i)
{
    rbtValue *v = n->value;
    if (i == 0)
        v->color = RED;
    else
        v->color = BLACK;
}

void insertionFixUp(rbt *b,bstNode *n)
{
    while ((n != b->tree->root) && (getColor(n->parent) == RED))
    {
        if (getColor(uncle(n)) == RED)
        {
            changeColor(n->parent,BLACK);
            changeColor(uncle(n),BLACK);
            changeColor(n->parent->parent,RED);
            n = n->parent->parent;
        }
        else
        {
            bstNode *p = n->parent;
            if (isLeftChild(n) != isLeftChild(n->parent))
            {
                bstNode *temp = n;
                if(isLeftChild(n) == 1)
                    rightRotate(b,n);
                else
                    leftRotate(b,n);
                temp = n;
                n = p;
                p = temp;
            }
            changeColor(p,BLACK);
            changeColor(p->parent,RED);
            if(isLeftChild(p) == 1)
                rightRotate(b,p);
            else
                leftRotate(b,p);
            break;
        }
    }
    changeColor(b->tree->root,BLACK);
}

void insertRBT(rbt *b,void *v)
{
    rbtValue *newV = newRBTvalue(b,v);
    bstNode *n = findBSTNode(b->tree,newV);
    if (n == NULL)
    {
        n = insertBST(b->tree,newV);
        insertionFixUp(b,n);
    }
    else
    {
        rbtValue *w = n->value;
        w->freq++;
    }
    b->words++;
    displayRBT(stdout,b);
}

int findRBT(rbt *b,void *v)
{
    rbtValue *newV = newRBTvalue(b,v);
    bstNode *found = findBSTNode(b->tree,newV);
    if (found != 0)
    {
        rbtValue *temp = found->value;
        fprintf(stdout,"%i",temp->freq);
    }
    return 0;
}

void deleteRBT(rbt *b,void *v)
{
    (void)b;
    (void)v;
}

int sizeRBT(rbt *b)
{
    return b->tree->size;
}

int wordsRBT(rbt *b)
{
    return b->words;
}

int getFreqR(rbt *b,void *v)
{
    if (findRBT(b,v) == 1)
    {
        rbtValue *w = v;
        return w->freq;
    }
    return 0;
}

void statisticsRBT(rbt *b,FILE *fp)
{
    fprintf(fp,"Words/Phrases: %i\n", wordsRBT(b));
    statisticsBST(b->tree,fp);
}

void displayRBT(FILE *fp,rbt *b)
{
    displayBST(fp,b->tree);
}


    
            
            
            
