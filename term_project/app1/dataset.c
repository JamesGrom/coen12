//James Grom
//dataset.c implementation of the abstract data type


#include"data.h"

//structure that holds data for an individual student
struct student
{
	int age;
	int id;
	STUDENT *next;
	STUDENT *prev;
};

//structure that holds pointer to array of student data, keeps track of how many students are present, 
struct class_year
{
	LIST **lists;//pointer to an array of list pointers
	int count;//count of total number of students in the college
	int length;//number that represents the length of the array of student structures
	int maxClassSize;//number that represents the maximum number of students allowed in the college
};

struct list
{
	int count;
	STUDENT *head;
};


//O(1) :constant as there are only 13 elements in the array
//creates the set, provides max number of students as the argument
//returns a pointer to the set
CY* createSet(int maxStudents)
{
	int i;
	CY *cyp;
	cyp=malloc(sizeof(CY));
	assert(cyp!=NULL);
	cyp->maxClassSize=maxStudents;
	cyp->count=0;
	cyp->length=13;//creating an array of list pointers with 1 list for each of the 13 ages
	cyp->lists=malloc(sizeof(LIST *)*13);
	assert(cyp->lists!=NULL);
	//create dummy nodes for each of the 13 lists
	for(i=0;i<13;i++)
	{
		cyp->lists[i]=malloc(sizeof(LIST));
		cyp->lists[i]->head=malloc(sizeof(STUDENT));
		assert(cyp->lists[i]!=NULL&&cyp->lists[i]->head!=NULL);
		cyp->lists[i]->head->prev=cyp->lists[i]->head;
		cyp->lists[i]->head->next=cyp->lists[i]->head;
		cyp->lists[i]->head->id=-1;
		cyp->lists[i]->count=0;
	}
	return cyp;
}

//O(n)- freeing each element in each list makes this O(n)
//destroys the set and frees memory
//possible segfault when deleting a list with a count=0
void destroySet(CY *cyp)
{
	assert(cyp!=NULL);
	int i,j;
	for(i=0;i<13;i++)
	{
		if(cyp->lists[i]->count>0)
		{
			
			STUDENT *pDel;
			STUDENT *pNext;
			pDel=cyp->lists[i]->head;
			do
			{
				pNext=pDel->next;
				free(pDel);
				pDel=pNext;
			}
			while(pDel!=cyp->lists[i]->head);
		}
		else
		{
			free(cyp->lists[i]->head);//free the dummy node if the list is empty
		}
	}
	free(cyp->lists);
	free(cyp);
	return;
}

//O(1)-finding the index of the list holding all students with given age
//O(n)-printing each element in the list
//net big O: O(n)-due to printing each element in the list
//returns -1 if nothing is found
//returns index of sought element if present
void searchAge(CY *cyp, int sought_age)
{
	assert(cyp!=NULL);
	int index=findIndex(cyp,sought_age);
	if(index==-1)
	{
		printf("there are no students enrolled with age = %d \n",sought_age);
	}
	else
	{
		//found the list of sought ages, indexed by variable index
		STUDENT *p;
		p=cyp->lists[index]->head;
		p=p->next;
		//print off all the students with that age
		printf("\n\n\nCOMMAND: search for students with age = %d\n",sought_age);
		while(p!=cyp->lists[index]->head)
		{
			printf("student id: %d student age: %d was found \n",p->id,p->age);
			p=p->next;
		}
	}
	return;
}




//O(1)
//returns index of list if sought age is present
//returns -1 if no students present with sought age
int findIndex(CY *cyp,int age)
{
	if(age>30||age<18)
	{
		return -1;
	}
	int index=age%18;
	if(cyp->lists[index]->count>0)
	{
		return index;
	}
	else
	{
		return -1;
	}
}





//O(1)
//inserts the student into the datastructure
void insertion(CY *cyp,int insertID,int insertAge)
{
	assert(cyp!=NULL);
	if(insertAge<18||insertAge>30)
	{
		printf("invalid age for entry \n");
		return;
	}
	int index=insertAge%18;
	STUDENT *temp;
	temp=malloc(sizeof(STUDENT));
	assert(temp!=NULL);
	temp->age=insertAge;
	temp->id=insertID;
	temp->prev=cyp->lists[index]->head;
	temp->next=cyp->lists[index]->head->next;
	cyp->lists[index]->head->next=temp;
	cyp->lists[index]->count++;
	cyp->count++;
	printf("Added student : %d age %d \n",insertID, insertAge);
	return;
}

//O(1)
//deletes all students with the given age
void deletion(CY *cyp,int deleteAge)
{
	assert(cyp!=NULL);
	if(deleteAge<18||deleteAge>30)
	{
		printf("invalid deletion request, non-viable age submitted \n");
		return;
	}
	int index = findIndex(cyp,deleteAge);
	if(index==-1)
	{
		printf("no students enrolled with that age \n");
		return;
	}
	STUDENT *pDel=cyp->lists[index]->head->next;
	printf("\n\n\nCOMMAND: delete students with age= %d \n",deleteAge);
	while(pDel!=cyp->lists[index]->head)
	{
		cyp->lists[index]->head->next=pDel->next;
		printf("student : %d  Age : %d was deleted \n",pDel->id,index+18);
		free(pDel);
		pDel=cyp->lists[index]->head->next;
		cyp->count--;
	}
	cyp->lists[index]->count=0;
	cyp->lists[index]->head->next=cyp->lists[index]->head;
	cyp->lists[index]->head->prev=cyp->lists[index]->head;
	return;
}
//O(1) -assuming the possible ages of enrollment are always betweenn 18 and 30
int maxAgeGap(CY *cyp)
{
	int min=0;
	int max=12;
	while(cyp->lists[min]->count==0)
	{
		min++;
		if(min>12)
		{
			printf("no students are present in the list \n");
			return -1;
		}
	}
	while(cyp->lists[max]->count==0)
	{
		max--;
	}
	printf("max age gap between students = %d years \n",max-min);
	return max-min;
}
