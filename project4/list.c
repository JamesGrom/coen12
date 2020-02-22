//James Grom
//Project4 -week 1
//Maze
#include"list.h"
#include<math.h>
#include<time.h>
#include<curses.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#define NODE struct node
//create the node structure
struct node
{
	NODE *next;
	NODE *prev;
	void *data;
};

//create the LIST structure 
typedef struct list
{
	int count;
	NODE *head;
	//NODE *tail;
	int (*compare)(); //function pointer
}LIST;
//skip function prototypes, as they're defined in list.h

//return a pointer to a new list usingcompareas its comparison function, which may be NULL
//O(1)
LIST *createList(int (*compare)())
{
	//initialize the LIST structure
	LIST *lp;
	lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count=0;
	lp->compare=compare;
	//initialize the dummy node
	NODE *dummy;
	dummy=malloc(sizeof(NODE));
	dummy->next=dummy;
	dummy->prev=dummy;
	dummy->data=NULL;
	//point the head pointer to the dummy node
	lp->head=dummy;
	return lp;
}

//deallocate memory associated with the list pointed to bylp
//O(n)
void destroyList(LIST *lp)
{
	assert(lp!=NULL);
	NODE *pDel, *pNext;
	pDel=lp->head;
	do
	{
		pNext = pDel ->next;
  		free(pDel);
   		pDel = pNext;
	}
   	while (pDel!= lp->head); 
	free(lp);

}

//return the number of items in the list pointed to by lp
//O(1)
int numItems(LIST *lp)
{
	assert(lp!=NULL);
	return lp->count;
}

//add item as the first item in the list pointed to bylp
//O(1)
void addFirst(LIST *lp, void *item)
{
	//assert that all the arguments are valid
	assert(lp!=NULL && item !=NULL);
	NODE *temp;
	temp=malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->data=item; 
	temp->prev=lp->head;
	temp->next=lp->head->next;
	lp->head->next->prev=temp;
	lp->head->next=temp;
	lp->count++;
}

//additemas the last item in the list pointed to bylp
//O(1)
void addLast(LIST *lp, void *item)
{
	//ensure valid arguments
	assert(lp!=NULL && item !=NULL);
	//allocate memory for new node
	NODE *temp;
	temp=malloc(sizeof(NODE));
	assert(temp!=NULL);
	//initialize node using argument item
	temp->data=item;
	//point the temp->next to lp->head and the temp->prev to lp->tail
	temp->next=lp->head;
	temp->prev=lp->head->prev;
	//point lp->tail->next to temp, lp->tail to temp and lp->head->prev to temp and  
	lp->head->prev->next=temp;
	//lp->tail=temp;
	lp->head->prev=temp;
	//increment the count
	lp->count++;
}


//remove and return the first item in the list pointed to bylp; the list must not be empty
//O(1)
void *removeFirst(LIST *lp)
{
	//ensure the list is not empty
	assert(lp!=NULL);
	//create a void *temp for the return value
	void *temp;
	//create a node pointer
	NODE *p;
	//point p to lp->head->next
	p=lp->head->next;
	if(p==lp->head)
	{
		return NULL;
	}
	//point lp->head->next to p->next
	lp->head->next=p->next;
	//point p->next->prev to lp->prev
	p->next->prev=p->prev;
	//initialize void *temp from p->data
	temp=p->data;
	//free p
	free(p);
	//count --
	lp->count--;
	//return void*temp
	return temp;
}

//remove and return the last item in the list pointed to bylp; the list must not be empty
//O(1)
void *removeLast(LIST *lp)
{
	assert(lp!=NULL &&lp->count>0);
	void *temp=NULL;
	NODE *p;
	p=lp->head->prev;
	p->prev->next=lp->head;
	lp->head->prev=p->prev;
	free(p);
	lp->count--;
	return temp;

}

//return, but do not remove, the first item in the list pointed to bylp; the list must not be empty
//O(1)
void *getFirst(LIST *lp)
{
	assert(lp!=NULL);
	NODE *p;
	p=lp->head->next;
	if(p==lp->head)
	{
		return NULL;
	}
	return p->data;
}

//return, but do not remove, the last item in the list pointed to bylp; the list must not be empty
//O(1)
void *getLast(LIST *lp)
{
	assert(lp!=NULL);
	if(lp->head->prev==lp->head)
	{
		return NULL;
	}
	NODE *p;
	p=lp->head->prev;
	return p->data;
}

//ifitemis present in the list pointed to bylpthen remove it; the comparison function must not be NULL
//O(n)
void removeItem(LIST *lp, void *item)
{
	//ensure valid arguments
	assert(lp!=NULL && item!=NULL && lp->compare!=NULL);
	//return if empty list
	if(lp->count<1)
	{
		return;
	}
	int comp;
	//create a NODE pointer pointing to dummy node 
	NODE *p=lp->head->next;
	while(p!=lp->head)
	{
		comp=(*lp->compare)(item,p->data);
		if(comp==0)
		{
			p->next->prev=p->prev;
			p->prev->next=p->next;
			lp->count--;
			free(p);
			return;
		}
		p=p->next;
	}
	return;
}


//ifitemis present in the list pointed to bylpthen return the matching item, otherwise returnNULL; the com-parison function must not beNULL
//O(n)
void *findItem(LIST *lp, void *item)
{
	//ensure valid arguments
	assert(lp!=NULL && item!=NULL && lp->compare!=NULL);
	//create a node pointer
	NODE *p=lp->head->next;
	int comp;
	while(p!=lp->head)
	{
		comp=(*lp->compare)(item,p->data);
		if(comp==0)
		{
			return p->data;
		}
		p=p->next;
	}
	return NULL;
}


//allocate and return an array of items in the list pointed to bylp
//O(n)
void *getItems(LIST *lp)
{
	assert(lp!=NULL);
	int i;
	void **temp;
	temp=malloc(sizeof(void *)*lp->count);
	assert(temp!=NULL);
	NODE *p=lp->head->next;
	i=0;
	for(i=0;i<lp->count;i++)
	{
		printf("%d \n",i);
		temp[i]=p->data;
		p=p->next;
	}
	return temp;
}

















