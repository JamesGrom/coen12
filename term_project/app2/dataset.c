//James Grom
//dataset.c implementation of the abstract data type
//Term Project: Application 2

#include"data.h"

//structure that holds data for an individual student
struct student
{
	int age;
	int id;
};

//structure that holds pointer to array of student data, keeps track of how many students are present, 
struct class_year
{
	STUDENT *students;//pointer to an array of student structures
	int count;//count of total number of students in the college
	int length;//number that represents the length of the array of student structures
};



//O(n)
//creates the set, provides max number of students as the argument
//returns a pointer to the set
CY* createSet(int maxStudents)
{
	int i;
	CY *cyp;
	cyp=malloc(sizeof(CY));
	assert(cyp!=NULL);
	cyp->count=0;
	cyp->length=maxStudents*2;//creating an array of student structures indexed by id, the max possible id = 2*maxStudents therefore 								that should be the length of the array 
	cyp->students=malloc(sizeof(STUDENT)*cyp->length);
	assert(cyp->students!=NULL);
	//initialize all the student structures with an age of -1 to denote that they are empty
	for(i=0;i<cyp->length;i++)
	{
		cyp->students[i].age=-1;
	}
	return cyp;
}

//O(1)
//destroys the set and frees memory
//frees the pointer to the hash table
void destroySet(CY *cyp)
{
	assert(cyp!=NULL);
	int i,j;
	free(cyp);
	return;
}

//identifies existence state of a given ID
//O(1)
void searchID(CY *cyp, int sought_ID)
{
	assert(cyp!=NULL);
	if(sought_ID<0||sought_ID>cyp->length-1)
	{
		printf("no student with that ID exists within our database \n");
		return;
	}
	else
	{
		if(cyp->students[sought_ID].age!=-1)
		{
			printf(" student found with ID: %d , AGE: %d\n",cyp->students[sought_ID].id,cyp->students[sought_ID].age);
			return;
		}
		else
		{
			printf("no student with that ID exists within our database \n");
			return;
		}
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
	if(insertID<0||insertID>cyp->length-1)
	{
		printf("invalid id entry \n");
		return;
	}
	STUDENT *temp;
	temp=malloc(sizeof(STUDENT));
	assert(temp!=NULL);
	temp->age=insertAge;
	temp->id=insertID;
	cyp->students[insertID]=*temp;
	cyp->count++;
	printf("Added student : %d age %d \n",insertID, insertAge);
	return;
}

//O(1)
void deletion(CY *cyp,int deleteID)
{
	assert(cyp!=NULL);
	if(deleteID<0||deleteID>cyp->length-1)
	{
		printf("invalid deletion request, non-viable age submitted \n");
		return;
	}
	if(cyp->students[deleteID].age==-1)
	{
		printf("no students enrolled with that age \n");
		return;
	}
	else
	{
		printf("student : %d  Age : %d was deleted \n",deleteID,cyp->students[deleteID].age);
		cyp->students[deleteID].age=-1;
		cyp->count--;
		return;
	}
}
















