//
//  huffman.c
//  
//
//  Created by James Grom on 2/21/20.
//

#include <stdio.h>

//James Grom
//project 25 week 2 -huffman coding
#include "pqueue.h"
#include "pack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#define NODE struct node
static int nodeCmp(NODE *, NODE *);
struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare)();
};
//main function O(n)
int main (int argc, char *argv[])
{
    FILE *fp;
    int counts[257];//257 used as size of array to reflect number of ascii characters plus 1 for EOF character
    NODE *leaves[257];//^
    int i;
    char temp;
    //initialize the counts array with 0's
    for(i=0;i<257;i++)
    {
        counts[i]=0;
        leaves[i]=NULL;
    }
    if(argc!=3)
    {
        printf("incorrect number of files\n");
        return 0;
    }
    if((fp=fopen(argv[1],"r"))==NULL)
    {
        printf("the name of the file is missing \n");
        return -1;
    }
    //step 1
    //counts the number of occurences of each character in the file and stores them indexed by int-cast character
    //--maybe the first character messes up the rest, the 012
    while(fscanf(fp,"%c",&temp)==1)
    {
        counts[(int)temp]++;
    }
    fclose(fp);
    //step 2
    //creates the binary tree/priorityqueue
    PQ *pq=createQueue(nodeCmp);
    //adds each character and number of occurences to the priority queue and creates array of pointers to nodes indexed by
    //their respective character
    for(i=0;i<257;i++)
    {
        //only include characters with a nonzero frequency within the minheap
        //also include the eof character (withindex 256, and count of 0)
        if(counts[i]>0||i==256)
        {
            leaves[i]=malloc(sizeof(NODE));
            leaves[i]->count=counts[i];
            leaves[i]->parent=NULL;
            addEntry(pq,leaves[i]);
        }

    }
    //add the EOF leaf as a special case (of 0 frequency)
    leaves[256]=malloc(sizeof(NODE));
    leaves[256]->count=0;
    leaves[256]->parent=NULL;
    addEntry(pq,leaves[256]);

    //step 3
    //sum the entries' data?
    while(numEntries(pq)>1)
    {
        NODE *child1;
        NODE *child2;
        NODE *temp_root=malloc(sizeof(NODE));
        assert(temp_root!=NULL);
        child1=removeEntry(pq);
        child2=removeEntry(pq);
        temp_root->parent=NULL;
        child1->parent=temp_root;
        child2->parent=temp_root;
        temp_root->count=(child1->count + child2->count);
        addEntry(pq,temp_root);
    }


    //step 5, assigning bit patterns to each character
    NODE *temp_node;
    for(i=0;i<257;i++)
    {
        if(leaves[i]!=NULL)
        {
            temp_node=leaves[i];
            int counter=0;
            while(temp_node->parent!=NULL)
            {
                counter++;
                temp_node=temp_node->parent;
            }
            int total=counter*counts[i];
            if(isprint(i)==0)
            {
                printf("%03o: %d x %d bits = %d bits\n",i,counts[i],counter,total);
            }
            else
            {
                printf("'%c': %d x %d bits = %d bits\n",i,counts[i],counter,total);
            }
        }
    }
    pack(argv[1],argv[2],leaves);
    printf("end \n");
    return 0;
}

   
//returns -1 if a<b
//returns 1 if a>b
//returns 0 if a==b
// >< points to lesser of the two
//O(1)
static int nodeCmp(NODE *a,NODE *b)
{
    assert(a!=NULL && b!=NULL);
    if(a->count>b->count)
    {
        return 1;
    }
    else if (a->count<b->count)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}



