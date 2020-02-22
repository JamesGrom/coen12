// James Grom
// Project 1: Counting number of words in a text file


//include necessary libraries
#include<stdio.h>
#include<string.h>

//prototypes for functions
void read_file (FILE *);

//argc gives number of arguments
//argv gives array of strings, each of which is one of the arguments of the program
int main (int argc, char *argv[])
{
	//if there's no file to be read, argc will be 1
	if(argc==1)
	{
		printf("the name of the file is missing \n");
		return 0;
	}
	//open the file and check if completed sucessfully
	FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("the file could not be opened\n ");
		return -1;
	}
	//reads the file of the given file pointer  and outputs the number of words
	read_file(fp);
	//close the file
	fclose(fp);
	return 1;
}

//output the number of words of the given file passed through the file pointer as an argument
void read_file (FILE *fp)
{
	int counter=0;
	char temp[30];
	while(fscanf(fp,"%s",temp)==1)
	{
		counter++;
	}
	printf("%d total words \n",counter);
	return;
	
}







