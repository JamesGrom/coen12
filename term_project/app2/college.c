//James Grom
//college.c
//main function
//Term Project: Application 2

#include"data.h"

#define MAXSTUDENTS 3000

int ID = 0;
//O(n)
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
	randomID=(rand()%2000);
	searchID(cy,randomID);
	randomID=(rand()%2000);
	printf(" %d random ID sought to delete \n",randomID);
	deletion(cy,randomID);
	destroySet(cy);

}






