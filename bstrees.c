#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include <string.h>
#include <ctype.h>
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
#include <stdlib.h>
#include "comparator.h"
#include "queue.h"
#include "stack.h"
#include "sll.h"
#include "dll.h"
#include "integer.h"
#include "real.h"
#include "str.h"

char* removeChar(char *str)
{
    int i,j,a;
    for(i = 0; str[i] != '\0'; ++i)
    {
        while (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || isspace(str[i]) || str[i] == '\0') )
        {
            for(j = i; str[j] != '\0'; ++j)
            {
                str[j] = str[j+1];
            }
            str[j] = '\0';
        }
    }
    for(a = 0; str[a] != '\0'; a++)
    {
        str[a] = tolower(str[a]);
    }
    return str;
}

char* removeSpaces(char *str){
    char *from, *to;
    int space = 0;
    to = from = str;
    while(1){
        if(space && *from == ' ' && to[-1] == ' ')
            ++from;
        else {
            space = (*from==' ')? 1 : 0;
            *to++ = *from++;
            if(!to[-1])
                break;
        }
    }
    return str;
}

int main(__attribute__ ((unused))int argc, char* argv [])
{
    FILE *fp1, *fp2, *output;
    char *x,v;
    if(argc == 5)
        output = fopen(argv[4],"w");
    else
        output = stdout;
    if (strcmp(argv[1],"-v") == 0)
    {
        vbst *t = newVBST(displayString,stringComparator);
        fp1 = fopen(argv[2], "r");
        if (fp1 == NULL)
        {
            printf("Error while opening file.\n");
            exit(EXIT_FAILURE);
        }
        if(stringPending(fp1) == 1)
        {
            x = readString(fp1);
        }else
        {
            x = readToken(fp1);
        }
        
        while(!feof(fp1))
        {
            x = removeChar(x);
            x = removeSpaces(x);
            insertVBST(t, x);
            if(stringPending(fp1) == 1)
            {
                x = readString(fp1);
                x = removeChar(x);
                x = removeSpaces(x);
                insertVBST(t,x);
            }
            x = readToken(fp1);
        }
        fclose(fp1);
        fp2 = fopen(argv[3], "r");
        if (fp2 == NULL)
        {
            printf("Error while opening file.\n");
            exit(EXIT_FAILURE);
        }
        char *z,*h;
        int o;
        v = readChar(fp2);
        while(!feof(fp2))
        {
            switch(v)
            {
                case 'i':
                    if(stringPending(fp2) == 1)
                    {
                        z = readString(fp2);
                        
                    }else
                    {
                        z = readToken(fp2);
                        
                    }
                    printf("Inserting: %s\n", z);
                    insertVBST(t, removeSpaces(removeChar(z)));
                    break;
                case 'd':
                    z = readToken(fp2);
                    printf("Deleting: %s\n", z);
                    deleteVBST(t, removeSpaces(removeChar(z)));
                    break;
                case 'f':
                    h = removeSpaces(removeChar(readToken(fp2)));
                    o = findVBST(t, h);
                    printf("Frequency of \"%s", h);
                    printf("\" is : %i\n", o);
                    break;
                case 's':
                    displayVBST(output,t);
                    break;
                case 'r':
                    statisticsVBST(t,output);
                    break;
            }
            v = readChar(fp2);
        }
        fclose(fp2);
    }else if (strcmp(argv[1],"-r") == 0)
    {
        fprintf(stdout,"here1\n");
        rbt *t = newRBT(displayString,stringComparator);
        fprintf(stdout,"here2\n");
        fp1 = fopen(argv[2], "r");
        if (fp1 == NULL)
        {
            printf("Error while opening file.\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stdout,"here3\n");
        if(stringPending(fp1) == 1)
        {
            x = readString(fp1);
        }else
        {
            x = readToken(fp1);
        }
        fprintf(stdout,"here4\n");
        while(x != NULL)
        {
            x = removeChar(x);
            x = removeSpaces(x);
            insertRBT(t, x);
            if(stringPending(fp1) == 1)
            {
                x = readString(fp1);
                x = removeChar(x);
                x = removeSpaces(x);
                insertRBT(t,x);
            }
            x = readToken(fp1);
        }
        fprintf(stdout,"here5\n");\
        fclose(fp1);
        fp2 = fopen(argv[3], "r");
        if (fp2 == NULL)
        {
            printf("Error while opening file.\n");
            exit(EXIT_FAILURE);
        }
        char *z,*h;
        int o;
        v = readChar(fp2);
        while(!feof(fp2))
        {
            switch(v)
            {
                case 'i':
                    if(stringPending(fp2) == 1)
                    {
                        z = readString(fp2);
                        
                    }else
                    {
                        z = readToken(fp2);
                        
                    }
                    printf("Inserting: %s\n", z);
                    insertRBT(t, removeSpaces(removeChar(z)));
                    break;
                case 'd':
                    z = readToken(fp2);
                    printf("Deleting: %s\n", z);
                    deleteRBT(t, removeSpaces(removeChar(z)));
                    break;
                case 'f':
                    h = removeSpaces(removeChar(readToken(fp2)));
                    o = findRBT(t, h);
                    printf("Frequency of \"%s", h);
                    printf("\" is : %i\n", o);
                    break;
                case 's':
                    displayRBT(output,t);
                    break;
                case 'r':
                    statisticsRBT(t,output);
                    break;
            }
            v = readChar(fp2);
        }
        fclose(fp2);
    }
    else
        fprintf(stderr,"Wrong format entered");
}
