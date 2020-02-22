//James Grom
//Project 2 unsorted
#include"set.h"//quotes used because I defined it, local file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


//create the structure for the set data type
typedef struct set
{
	char **data;//pointer to the array of character pointers, each pointing to a string element
	int length;// number that represents the length of the array of character pointers, determines max number of allowable elements. don't exceed!
	int count;// number that represents the number of strings held in the set
}SET;

//prototype for the private function search 
static int search(SET *,char *);

//function used to create a set, user provides maximum number of strings to be held, in maxElts.
SET *createSet(int maxElts)
{
	SET *sp; //pointer to the structure SET 
	sp=malloc(sizeof(SET)); // allocate memory for the structure sp  pointer to point to, no longer garbage
	assert(sp!=NULL); //stop the program and print error code if there's a malloc error. stop if memory can't be allocated for sp
	sp->length=maxElts;//holds the length of the array, determined by max number of elements, only allocated enough memory for that
	sp->count=0;//initialize the number of strings to be 0 because there are no strings held at the beginning
	sp->data=malloc(sizeof(char*)*maxElts);//allocate memory for array of pointers to the strings. doesn't allocate memory for the strings themselves
	assert(sp->data!=NULL);//ensure memory was properly allocated for the array of character pointers
	return sp;//return the pointer to the created set
}

//frees memory associated with the set, subsequently deleting the set data 
void destroySet(SET *sp)
{
	assert(sp!=NULL);//ensure that the set isn't empty
	for(int i=0;i<sp->count;i++)//delete each string stored in the set by freeing each pointer in the char pointer array
	{
		free(sp->data[i]);
	}
	free(sp->data);//free pointer to the  array of char pointers, subsequently destroying the array of char pointers
	free(sp);//free pointer to the structure SET
	return;
}

//return the number of elements in the set pointed to by sp
int numElements(SET *sp)
{
	return sp->count;
}

//add the given string into the set
void addElement(SET *sp,char *elt)
{   //search the set to see if elt is unique, if not don't add the element
  	//make sure set has room for another string, if not don't add the element
	assert(sp->count<sp->length);
	if(search(sp,elt)!=-1)//ensure that the inserted element is unique, return if not
	{
		return;
	}
	sp->data[sp->count]=strdup(elt);//allocate memory,copy string, return pointer to copy
	sp->count++;//account for the addition of a new element
	return;
}

//remove the given string from the set
void removeElement(SET *sp,char *elt)
{
	//ensure that set is not empty
	assert(sp!=NULL);
	int index=search(sp,elt);//find the index of the sought string
	if(index==-1)//ensure that the string exists in the array of char pointers
	{
		return;
	}
	sp->count--;//decrement the counter to adjust for the removed element	
	sp->data[index]=sp->data[sp->count];//put the last element into the index of the removed string
	return;
}

//return input string if the string is within the set, otherwise return null
char *findElement(SET *sp,char *elt)
{
	int index=search(sp,elt);
	if(index==-1)//if the string doesn't exist within the set, return null
	{
		return NULL;
	}
	return sp->data[index];//return the string if it's found within the set 
}

//allocate and return a set pointer to a set identical to the argument set
char ** getElements(SET *sp)
{
	char **temp=malloc(sizeof(char*)*sp->count);//allocates the minimum amount of  memory for the array of element pointers
	assert(temp!=NULL);//ensure no malloc error
	memcpy(temp,sp->data,sizeof(char*)*sp->count);//copy and allocate the memory for the new array of char pointers 
	return temp;
}

//returns index of sought element
//if element is not within the set, returns -1
static int  search(SET *sp, char *elt)
{
	int i;
	for(i=0;i<sp->count;i++)
	{
		if(strcmp(sp->data[i],elt)==0)
		{
			return i;
		}
	}
	return -1;
}

 
 
 
 
 
