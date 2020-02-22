//James Grom
//Project 3 string-hash
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


//3---
//create the structure for the set data type
typedef struct set
{
	char **data;//pointer to the array of character pointers, each pointing to a string element
	char  *flag;//parallel array used to keep track of which indexes have what element status
	int length;// number that represents the length of the array of character pointers, determines max number of allowable elements. don't exceed!
	int count;// number that represents the number of strings held in the set
}SET;

//3---
//prototype for the private function search 
static unsigned search(SET *,char *,bool *);

//3___
//prototype for the private hash function
unsigned strhash (char *s); 
//3---
//function used to create a set, user provides maximum number of strings to be held, in maxElts.
SET *createSet(int maxElts)
{
	SET *sp; //pointer to the structure SET 
	sp=malloc(sizeof(SET)); // allocate memory for the structure sp  pointer to point to, no longer garbage
	assert(sp!=NULL); //stop the program and print error code if there's a malloc error. stop if memory can't be allocated for sp
	assert(maxElts>0); // make sure maxElts is inputted correctly
	sp->length=maxElts;//holds the length of the array, determined by max number of elements, only allocated enough memory for that
	sp->count=0;//initialize the number of strings to be 0 because there are no strings held at the beginning
	sp->data=malloc(sizeof(char*)*maxElts);//allocate memory for array of pointers to the strings. doesn't allocate memory for the strings themselves
	assert(sp->data!=NULL);//ensure memory was properly allocated for the array of character pointers
	sp->flag=malloc(sizeof(char)*maxElts);//allocate memory for array of strings keeping track of index status
	assert(sp->flag!=NULL);//ensure memory was properly allocated for the array of character pointers
	int i;
	//initialize the flag array to have all slots= E
	for(i=0;i<maxElts;i++)
	{
		sp->flag[i]=EMPTY;
	}
	return sp;//return the pointer to the created set
}

//3---
//frees memory associated with the set, subsequently deleting the set data 
void destroySet(SET *sp)
{
	assert(sp!=NULL);//ensure that the set isn't empty
	for(int i=0;i<sp->length;i++)//delete each string stored in the set by freeing each pointer in the char pointer array
	{
		if(sp->flag[i]==FILLED)
		{
			free(sp->data[i]);
		}
	}
	free(sp->data);//free pointer to the  array of char pointers, subsequently destroying the array of char pointers
	free(sp->flag);//free pointer to array of index flags, subsequently destroying the array of char pointers
	free(sp);//free pointer to the structure SET
	return;
}

//3---
//return the number of elements in the set pointed to by sp
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

//3---
//add the given string into the set
void addElement(SET *sp,char *elt)
{   //search the set to see if elt is unique, if not don't add the element
  	//make sure set has room for another string, if not don't add the element
	assert(sp->count<sp->length);
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found=false;
	unsigned index;
	index=search(sp,elt,&found);//assume search function returns index where the element shoud be inserted
	if(found==true)//ensure that the inserted element is unique
	{
		return;
	}
	//assert(sp->data[index]!=NULL);
	elt=strdup(elt);
	assert(elt!=NULL);
	sp->data[index]=elt;//allocate memory,copy string, return pointer to copy
	sp->flag[index]=FILLED;//edit the flag to show there's a string in that index
	sp->count++;//account for the addition of a new element
	return;
}

//3--_ ensure that using a \0 as a delete character is appropriate
//remove the given string from the set
void removeElement(SET *sp,char *elt)
{
	//ensure that set is not empty
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found = false;
	unsigned index=search(sp,elt,&found);//find the index of the sought string
	if(found==false)//ensure that the string exists in the array of char pointers
	{
		return;
	}
	sp->count--;
	sp->flag[index]=DELETED;
	free(sp->data[index]);
	return;
}

//3---
//return input string if the string is within the set, otherwise return null
char *findElement(SET *sp,char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;
	int index=search(sp,elt, &found);
	if(found==false)//if the string doesn't exist within the set, return null
	{
		return NULL;
	}
	return sp->data[index];//return the string if it's found within the set 
}


//3 ___
//allocate and return an array of elements in the set pointed to bysp
char ** getElements(SET *sp)
{
	int i,j;
	char **temp;
	assert(sp!=NULL);
	temp=malloc(sizeof(char*)*sp->count);//allocates the minimum amount of  memory for the array of element pointers
	assert(temp!=NULL);//ensure no malloc error
	j=0;
	for (i=0;i<sp->length;i++)
	{
		if(sp->flag[i]==FILLED)
		{
			temp[j]=strdup(sp->data[i]);
			j++;
		}
	}
	return temp;
}


//3--_
//returns index of sought element
//the boolean found denotes if the element is within the set
//uses the given hash function in order to find the appropriate index for the given key elt
static unsigned  search(SET *sp, char *elt, bool *found)
{
	unsigned int index;
	int first_del=-1;
	int first=0;
	unsigned int start;
	start=strhash(elt);//yeilds a number unique to key elt
	start=(start%(sp->length));//yeilds the home adress for that key 
	//char *state=flag[index];//set up a pointer to the first index yeiled by the hash function		
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
			if(strcmp(sp->data[index],elt)==0)
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


//3___
//given hash function used 
//returns the numerator used with %maxElts to yeild the index of the given key
unsigned strhash(char *s)
{
	unsigned hash = 0;

	while(*s!='\0')
	{
		hash = 31 * hash + *s ++;
	}
	return hash;
}



























