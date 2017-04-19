//
//  bst.c
//  Assign3
//
//  Created by Grace Benway on 3/30/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"
#include "stack.h"
#include "sll.h"
#include "dll.h"
#include "integer.h"
#include "real.h"
#include "str.h"

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *))
{
    bst *new = (bst*)malloc(sizeof(bst));
    if (new == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    new->compare = c;
    new->display = d;
    new->size = 0;
    new->root = NULL;
    return new;
}

bstNode *newbstNode(void *v)
{
    bstNode *new = (bstNode*)malloc(sizeof(bstNode));
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    new->value = v;
    return new;
}

static bstNode *insertNode(bst *b,bstNode *n,bstNode *t)
{
    if (b->compare(t->value,n->value) < 0)
    {
        if (n->left == NULL)
        {
            t->parent = n;
            n->left = t;
        }else
            t = insertNode(b,n->left,t);
    }else
    {
        if (n->right == NULL)
        {
            t->parent = n;
            n->right = t;
        }else
            t = insertNode(b,n->right,t);
    }
    return t;
}

bstNode *insertBST(bst *b,void *v)
{
    bstNode *t = newbstNode(v);
    if (b->root == NULL)
    {
        t->parent = t;
        b->root = t;
        return t;
    }else
        insertNode(b,b->root,t);
    b->size++;
    return t;
}

void del(bst *b, void *v)
{
    bstNode *f = findBSTNode(b,v);
    if(f != NULL)
    {
        f = swapToLeafBSTNode(f);
        pruneBSTNode(b,f);
    }
    else
        fprintf(stderr,"Value x not found");
}

int findBST(bst *b,void *v)
{
    bstNode *found = findBSTNode(b,v);
    if (found != NULL)
        return 1;
    return 0;
}

static bstNode *find(bst *b,bstNode *n, void *v)
{
    if (n == NULL)
        return 0;
    int result = b->compare(v,n->value);
    if (result == 0)
    {
        return n;
    }else if (result < 0)
    {
        return find(b,n->left,v);
    }else
        return find(b,n->right,v);
}

bstNode *findBSTNode(bst *b,void *v)
{
    return find(b,b->root,v);
}

static bstNode *findMax(bstNode *n)
{
    while (n->right != NULL)
        n = n->right;
    return n;
}

static bstNode *findMin(bstNode *n)
{
    while (n->left != NULL)
        n = n->left;
    return n;
}

static bstNode *findPred(bstNode *n)
{
    if (n->left != NULL)
        return findMax(n->left);
    bstNode *p = n->parent;
    while(p != NULL && n == p->left)
    {
        n = p;
        p = p->parent;
    }
    return p;
}

static bstNode *findSuc(bstNode *n)
{
    if (n->right != NULL)
        return findMin(n->right);
    bstNode *p = n->parent;
    while (p != NULL && n == p->right)
    {
        n = p;
        p = p->parent;
    }
    return p;
}

bstNode *swapToLeafBSTNode(bstNode *n)
{
    if (n->right == NULL && n->left == NULL)
        return n;
    bstNode *np = NULL;
    if (n->left != NULL)
        np = findPred(n);
    else
        np = findSuc(n);
    n->value = np->value;
    return swapToLeafBSTNode(np);
}


void pruneBSTNode(bst *b,bstNode *n)
{
    if(n == n->parent->right)
        n->parent->right = NULL;
    else
        n->parent->left = NULL;
    n->parent = NULL;
    b->size--;
}

int sizeBST(bst *b)
{
    return b->size;
}

static int minD(bst *b, bstNode *n)
{
    if (n == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = minD(b, n->left);
        int rheight = minD(b, n->right);
        
        /* use the larger one */
        if (lheight < rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

int minDepth(bst *b)
{
    int h = minD(b, b->root);
    return h;
}

static int isLeaf(bstNode *a)
{
    if((a->left == NULL) && (a->right == NULL))
    {
        return 0;
    }
    return 1;
}

static int maxD(bst *t, bstNode *a) //maxDepth
{
    if (a == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = maxD(t, a->left);
        int rheight = maxD(t, a->right);
        
        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

int maxDepth(bst *t)
{
    int h = maxD(t, t->root);
    return h;
}


static int type(bst *b,bstNode *a)
{
    if((b->compare(a->value, a->parent->value)) < 0)
        return 0;
    return 1;
}

/* Print nodes at a given level */
void printGivenLevel(bst *b, bstNode* a, int level, FILE *f)
{
    char *t = "WRONG";
    if (a == NULL)
    {
        return;
    }
    if (level == 1)
    {
        if (a->parent == a)
            t = "-";
        else if (type(b,a) == 0)
            t = "-l";
        else
            t = "-r";
        if (isLeaf(a) == 0)
        {
            fprintf(f,"=");
            b->display(f,a->value);
            fprintf(f,"(");
            b->display(f,a->parent->value);
            fprintf(f,")");
            fprintf(f,"%s",t);
        }else
        {
            b->display(f,a->value);
            fprintf(f,"(");
            b->display(f,a->parent->value);
            fprintf(f,")");
            fprintf(f,"%s",t);
        }
    }
    if (level > 1)
    {
        printGivenLevel(b,a->right, level-1, f);
        printGivenLevel(b,a->left, level-1, f);
    }
}

void statisticsBST(bst *b,FILE *f)
{
    fprintf(f,"Nodes: %i\n", sizeBST(b));
    fprintf(f,"Minimum Depth: %i\n", minDepth(b));
    fprintf(f,"Maximum Depth: %i\n", maxDepth(b));
}

void displayBST(FILE *fp,bst *b)
{
    int h = maxDepth(b);
    int i;
    for (i = 1; i <= h; i++)               
    {
        printGivenLevel(b,b->root, i, fp);
        fprintf(fp,"\n");
    }
}

