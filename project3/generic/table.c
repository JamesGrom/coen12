//James Grom
//Project 3 generic
//Q --- make sure set.h is included in project directory
#include"set.h"//quotes used because I defined it, local file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>

//define the empty/filled/deleted constants
#define EMPTY 0
#define FILLED 1
#define DELETED 2


//3.2---
//create the structure for the set data type
typedef struct set
{
	void **data;//pointer to the array of void  pointers, each pointing to a generic element
	int (*compare)();//function pointer to the compare function supplied by the outsider program   
	unsigned (*hash)();//function pointer to the hash function supplied by the outsider program
	char *flag;//parallel array used to keep track of which indexes have what element status
	int length;// number that represents the length of the array of character pointers, determines max number of allowable elements. don't exceed!
	int count;// number that represents the number of strings held in the set
}SET;

//3.2---
//prototype for the private function search 
static unsigned search(SET *,void *,bool *);

//3.2-__
//function used to create a set, user provides maximum number of strings to be held, in maxElts.
//user also provides function pointers to their hash and compare functions 
//returns a set pointer to the set structure
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{	
	//ensure that all arguments provided are resonable
	assert(maxElts>0);
	assert(compare!=NULL);
	assert(hash!=NULL);
	
	//allocate data for the set structure	
	SET *sp; //pointer to the structure SET 
	sp=malloc(sizeof(SET)); // allocate memory for the structure sp  pointer to point to, no longer garbage
	assert(sp!=NULL); //stop the program and print error code if there's a malloc error. stop if memory can't be allocated for sp
	
	//initialize all the structure members to the appropriate values and allocate appropriate memory	
	sp->length=maxElts;//holds the length of the array, determined by max number of elements, only allocated enough memory for that
	sp->count=0;//initialize the number of strings to be 0 because there are no strings held at the beginning
	sp->data=malloc(sizeof(void *)*maxElts);//allocate memory for array of pointers to the strings. doesn't allocate memory for the strings themselves
	assert(sp->data!=NULL);//ensure memory was properly allocated for the array of character pointers
	sp->flag=malloc(sizeof(char)*maxElts);//allocate memory for array of strings keeping track of index status
	assert(sp->flag!=NULL);//ensure memory was properly allocated for the array of character pointers
	sp->compare=compare;//holds the pointer to the compare function within the set structure
	sp->hash=hash;//holds the pointer to the hash function within the set structure

	int i;
	//initialize the flag array to have all slots= E
	for(i=0;i<maxElts;i++)
	{
		sp->flag[i]=EMPTY;
	}
	return sp;//return the pointer to the created set
}

//3.2--_
//frees memory associated with the set structure, doesn't delete memory allocated by the outsider program.
//doesn't free memory for each individual element
//therefore, ensure destroySet is called after each individual element memory is freed 
void destroySet(SET *sp)
{
	assert(sp!=NULL);//ensure that the set isn't empty
	free(sp->data);//free pointer to the  array of void pointers, subsequently destroying the array of void pointers
	free(sp->flag);//free pointer to array of index flags, subsequently destroying the array of integers
	free(sp);//free pointer to the structure SET
	return;
}

//3.2---
//return the number of elements in the set pointed to by sp
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

//3.2---
//add the given generic element into the set
//only insert into the set if the element is unique
//assume that memory for the element was allocated in the outsider program before this function was called 
void addElement(SET *sp,void *elt)
{	
	//make sure set has room for another element, if not don't add the element
	assert(sp->count<sp->length);

	//ensure arguments are valid
	assert(sp!=NULL);
	assert(elt!=NULL);
	
	//initialize necessary local variables
	bool found=false;
	unsigned index;
	index=search(sp,elt,&found);//assume search function returns index where the element shoud be inserted
	if(found==true)//ensure that the inserted element is unique
	{
		return;
	}
	sp->data[index]=elt;//reference element in the appropriate index of the array of void pointers
	sp->flag[index]=FILLED;//edit the flag to show there's a string in that index
	sp->count++;//account for the addition of a new element
	return;
}

//3.2--_
//remove the given element from the set
//assume outside program frees the appropriate memory after this function is called
void removeElement(SET *sp,void *elt)
{
	//ensure that set is not empty and arguments are valid
	assert(sp!=NULL);
	assert(elt!=NULL);

	//define and initialize necessary local variables
	bool found = false;
	unsigned index=search(sp,elt,&found);//find the index of the sought element
	
	//ensure that the element exists in the array of element pointers
	if(found==false)
	{
		return;
	}

	//make the changes within the set structure to acknowledge a removed element
	sp->count--;
	sp->flag[index]=DELETED;
	return;
}

//3.2---
//return pointer to input element in set if the element is within the set, otherwise return null
void *findElement(SET *sp,void *elt)
{
	//ensure valid function arguments
	assert(sp!=NULL);
	assert(elt!=NULL);
	
	//define and initialize necessary local variables
	bool found=false;
	int index=search(sp,elt, &found);
	if(found==false)//if the element doesn't exist within the set, return null
	{
		return NULL;
	}

	return sp->data[index];//return a pointer to the element if it's found within the set 
}


//3.2 --_
//allocate and return an array of elements in the set pointed to by sp
void *getElements(SET *sp)
{
	int i,j;
	void **temp;
	assert(sp!=NULL);
	temp=malloc(sizeof(void*)*sp->count);//allocates the minimum amount of  memory for the array of element pointers
	assert(temp!=NULL);//ensure no malloc error
	j=0;
	for (i=0;i<sp->length;i++)
	{
		if(sp->flag[i]==FILLED)
		{
			temp[j]=sp->data[i];
			j++;
		}
	}
	return temp;
}


//3.2--_
//returns index of sought element
//the boolean found denotes if the element is within the set
//uses the given outside program hash function in order to find the appropriate index for the given key elt
//uses the outsider program compare function to decipher ordering
static unsigned  search(SET *sp, void *elt, bool *found)
{
	//define/initialize necessary local variables
	unsigned int index;
	int first_del=-1;
	int first=0;
	unsigned int start;
	start=(*sp->hash)(elt);//yeilds a number unique to key elt
	start=(start%(sp->length));//yeilds the home adress for that key 
	//traverse the flag array until it reaches the point it started from, acknowledged by start	
	//or until it finds an full slot with the same element or reaches and empty
	int i=0;
	for(int i=0;i<sp->length;i++)
	{
		index=(start+i)%sp->length;
		if(sp->flag[index]==EMPTY)
		{
			if(first_del!=-1)
			{
				*found=false;
				return first_del;
			}
			else
			{
				*found=false;
				return index;
			}
		}
		if(sp->flag[index]==FILLED)
		{
			if((*sp->compare)(sp->data[index],elt)==0)
			{
				*found=true;
				return index;
			}
		}
		if(sp->flag[index]==DELETED &&first ==0)
		{
			first_del=index;
			first=1;//prevents first_del from being updated after the first delete encountered
		}
	}
	*found=false;//an equivalent filled spot was never found
	return first_del;

}

























