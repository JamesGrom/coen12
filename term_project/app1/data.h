//James Grom
//data.h file
#ifndef DATA_H
#define DATA_H


#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct student STUDENT;
typedef struct class_year CY;
typedef struct list LIST;


CY* createSet(int maxStudents);
void destroySet(CY *cyp);
void searchAge(CY *cyp,int sought_age);
void insertion(CY *cyp, int insertID,int insertAge);
void deletion(CY *cyp, int deleteAge);
int maxAgeGap(CY*cyp);
int findIndex(CY *cyp,int age);



#endif
