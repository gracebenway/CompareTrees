//
//  vbst.h
//  Assign3
//
//  Created by Grace Benway on 4/3/17.
//  Copyright © 2017 Grace Benway. All rights reserved.
//

#ifndef vbst_h
#define vbst_h

#include <stdio.h>
#include "bst.h"

typedef struct vbst
{
    bst *tree;
    void (*display)(FILE *,void *);
    int (*compare)(void *,void *);
    int size;
    int words;
} vbst;

extern vbst *newVBST(void (*)(FILE *,void *),int (*)(void *,void *));
extern void insertVBST(vbst *,void *);
extern int findVBST(vbst *,void *);
extern void deleteVBST(vbst *,void *);
extern int sizeVBST(vbst *);
extern int wordsVBST(vbst *);
extern void statisticsVBST(vbst *,FILE *);
extern void displayVBST(FILE *,vbst *);
extern void checkVBST(vbst *);               //optional
#endif

