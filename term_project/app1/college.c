//James Grom
//college.c
//main function
//Term Project: Application 1


#include"data.h"

#define MAXSTUDENTS 3000

int ID = 0;
//O(n)- insertion into the linked list indexed by age
int main()
{
	CY *cy;
	cy=createSet(MAXSTUDENTS);
	srand(time(NULL));
	int studentNumber=0;
	int randomID;
	int randomAge;
	//generate 1000 student records
	while(studentNumber<1001)
	{
		randomID=(rand()%2)+1;
		randomAge=(rand()%13)+18;
		ID+=randomID;
		insertion(cy,ID,randomAge);
		studentNumber++;
	}
	//generate random student record and try to find it
	randomAge=(rand()%13)+18;
	randomID=(rand()%2000);
	searchAge(cy,randomAge);
	randomAge=(rand()%13)+18;
	printf(" %d random age sought to delete \n",randomAge);
	deletion(cy,randomAge);
	maxAgeGap(cy);
	//printf("max age gap : %d years \n",maxAgeGap(cy));
	destroySet(cy);

}






