//
//  pqueue.c
//  
//
//  Created by James Grom on 2/21/20.
//

#include <stdio.h>


//James Grom
//Project 5 week 1 -priority queue
#include"pqueue.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>

 
//create the pq structure prototype
struct pqueue
{
    int count;//numer of entries in the array
    int length;//length of allocated array
    void **data;//pointer to allocated array of data elements
    int (*compare)();//comparison function used to compare generic data being stored
};
//define functions for relationships between data in a heap
#define par(x) (((x)-1)/2)
#define l_ch(x) ((2*(x))+1)
#define r_ch(x) ((2*(x))+2)


//define the initial size of the array before any reallocations
#define START_SIZE 10
//no need to include function prototypes as they're included in pqeueu.h


//create the queue with input comparison function
//O(1);
PQ *createQueue(int (*compare)())
{
    PQ *pq;//pointer to priority queue structure
    pq=malloc(sizeof(PQ));// allocate memory for the structure
    assert(pq!=NULL);//ensure memory was allocated properly
    pq->count=0;
    //create and allocate initial memory for the data array
    pq->data=malloc(sizeof(void *)* START_SIZE);
    assert(pq->data!=NULL);
    pq->length=START_SIZE;
    pq->compare=compare;
    return pq;
}

//O(1)
//destroys the queue
void destroyQueue(PQ *pq)
{
    assert(pq!=NULL);//ensure valid argument
    free(pq->data);//free array pointer
    free(pq);//free structure pointer
    return;
}

//O(1)
int numEntries(PQ *pq)
{
    assert(pq!=NULL);
    return pq->count;
}

//O(n)
//adds an entry into the queue
void addEntry(PQ *pq, void *entry)
{
    assert(pq!=NULL);//ensure valid arguments
    //if the array will overflow when another data point is added,
    //double the array size to create space
    if(pq->count +1 >pq->length)
    {
        pq->data=realloc(pq->data,sizeof(void *)*pq->length *2);
        pq->length=pq->length*2;
    }
    //place new element at the end of binary heap
    //assume outside program allocated memory for the element
    pq->data[pq->count]= entry;
    int i =pq->count;
    pq->count++;
    //now reheap up

    int parent = par(i);
    //while the index is not outside domain
    while( parent>=0)
    {
        if((*pq->compare)(pq->data[parent],pq->data[i])>0)
        {
            void *temp= pq->data[parent];
            pq->data[parent]=pq->data[i];
            pq->data[i]=temp;
            i=parent;//acknowledge new index of element being added
        }
        else
        {
            break;
        }
        parent=par(i); // find new parent relative to element location
    }
    return;
}

//removes entry from the queue
//O(n)
void *removeEntry(PQ *pq)
{
    assert(pq!=NULL);
    void *root;
    root= pq->data[0];
    int comp;
    void *temp;
    int parent=0;
    int new_indx=0;
    pq->data[0]=pq->data[pq->count-1];
    pq->count--;
    while(l_ch(parent)<pq->count)
    {
        if(r_ch(parent)<pq->count)
        {
            comp=(*pq->compare)(pq->data[l_ch(parent)],pq->data[r_ch(parent)]);
            if(comp<0)
            {
                new_indx=l_ch(parent);
            }
            else
            {
                new_indx=r_ch(parent);
            }
        }
        else
        {
            new_indx=l_ch(parent);
        }
        if(((*pq->compare)(pq->data[parent],pq->data[new_indx]))>0)
        {
            temp=pq->data[parent];
            pq->data[parent]=pq->data[new_indx];
            pq->data[new_indx]=temp;
        }
        else
        {
            break;
        }
        parent=new_indx;
    }
    return root;
}

