//James Grom
//Project 4 
#include"set.h"//quotes used because I defined it, local file
#include"list.h"
#include<math.h>
#include<time.h>
#include<string.h>
#include<curses.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

int average= 20;
#define NODE struct node
//assume LIST and NODE are defined in list.h 


//O(1)
struct node
{
	NODE *next;
	NODE *prev;
	void *data;
};

typedef struct list 
{
	NODE *head;
	int count;
	int (*compare)();
}LIST;

//create the structure for the set data type
//O(1)
struct set
{
	LIST **lists; //pointer to array of list pointers 
	int (*compare)();//function pointer to the compare function supplied by the outsider program   
	unsigned (*hash)();//function pointer to the hash function supplied by the outsider program
	int length;// number that represents the length of the array of character pointers, determines max number of allowable elements. don't exceed!
	int count;// number that represents the number of strings held in the set
};

//function used to create a set, user provides maximum number of elements to be held, in maxElts.
//user also provides function pointers to their hash and compare functions 
//returns a set pointer to the set structure
//O(1)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{	
	//ensure that all arguments provided are resonable
	assert(maxElts>0);
	assert(compare!=NULL);
	assert(hash!=NULL);	
	//allocate data for the set structure	
	int i;
	SET *sp; //pointer to the structure SET 
	sp=malloc(sizeof(SET)); // allocate memory for the structure sp  pointer to point to, no longer garbage
	assert(sp!=NULL); //stop the program and print error code if there's a malloc error. stop if memory can't be allocated for sp
	//initialize all the structure members to the appropriate values and allocate appropriate memory	
	sp->length=maxElts/average;//holds the length of the array, determined by max number of elements and average # of elements, only allocated enough memory for that
	sp->count=0;//initialize the number of elements to be 0 because there are no elements held at the beginning
	sp->compare=compare;
	sp->hash=hash;
	//allocate memory for the array of list pointers. doesn't allocate memory for the lists themselves
	sp->lists=malloc(sizeof(LIST*)*sp->length);
	assert(sp->lists!=NULL);//ensure memory was properly allocated for the array of character pointers
	//initialize the array of list pointers with sentinel carrying lists
	for(i=0;i<sp->length;i++)
	{
		sp->lists[i]=createList(compare);
	}	
	return sp;//return the pointer to the created set
}



//frees memory associated with the set structure, doesn't delete memory allocated by the outsider program.
//doesn't free memory for each individual element
//therefore, ensure destroySet is called after each individual element memory is freed 
//O(n)
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	int i;	
	for(i=0;i<sp->length;i++)
	{
		free(sp->lists[i]);
	}
	free(sp->lists);
	free(sp);
	return;
}

//return the number of elements in the set pointed to by sp
//O(1)
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

//add the given generic element into the set
//only insert into the set if the element is unique
//assume that memory for the element was allocated in the outsider program before this function was called 
//O(n) - due to search
void addElement(SET *sp,void *elt)
{	
	//ensure arguments are valid
	assert(sp!=NULL);
	assert(elt!=NULL);
	int index= ((*sp->hash)(elt)) % (sp->length);
	if(findItem(sp->lists[index],elt)==NULL)
	{
		addFirst(sp->lists[index],elt);
		sp->count++;
	}
	return;
}


//remove the given element from the set
//assume outside program frees the appropriate memory after this function is called
//O(n)
void removeElement(SET *sp,void *elt)
{
	//ensure that set is not empty and arguments are valid
	assert(sp!=NULL);
	assert(elt!=NULL);
	int index;
	index=((*sp->hash)(elt)) % (sp->length);
	if(findItem(sp->lists[index],elt)!=NULL)
	{
		removeItem(sp->lists[index],elt);
		sp->count--;
	}
	return;
}

//return pointer to input element in set if the element is within the set, otherwise return null
//O(n)
void *findElement(SET *sp,void *elt)
{
	//ensure valid function arguments
	assert(sp!=NULL);
	assert(elt!=NULL);
	int index;
	index=((*sp->hash)(elt)) % (sp->length);
	return findItem(sp->lists[index],elt);
}


//allocate and return an array of elements in the set pointed to by sp
//O(n)
void *getElements(SET *sp)
{
	void **temp;
	assert(sp!=NULL);
	temp=malloc(sizeof(void*)*sp->count);//allocates the minimum amount of  memory for the array of element pointers
	assert(temp!=NULL);//ensure no malloc error
	int i,j=0,count;
	for (i=0;i<sp->length;i++)
	{	
		printf("%d \n",i);	
		count=numItems(sp->lists[i]);
		//j+=count;
		memcpy(temp+j,getItems(sp->lists[i]),sizeof(void *)*count);
		j+=count;
	}
	return temp;
}	
				
		























