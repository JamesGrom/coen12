//James Grom
//data.h file
//Term Project: Application 2
#ifndef DATA_H
#define DATA_H


#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct student STUDENT;
typedef struct class_year CY;


CY* createSet(int maxStudents);
void destroySet(CY *cyp);
void searchID(CY *cyp,int sought_ID);
void insertion(CY *cyp, int insertID,int insertAge);
void deletion(CY *cyp, int deleteID);



#endif
