// topic: program that is able to count the number of occurence of string mur

// libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// types, constance declarations


// functions prototypes



// main function declaration
int main(int argc,char *argv[])
{
	// main variables declarations
	int counter = 0; // variable which contains the occurences of mur
	int step = -1; // variable which indicate at which string recognize level we are
	FILE *input; // variable which reference the file I/O stream content

	// resolution process
	// step 1: make sure that the input patch is not empty
	char** param = argv;
	printf("size of parameter %ld",(int)sizeof(param)/sizeof(param[0]));
	if((int)sizeof(param)/sizeof(param[0]) < 1)
	{
		printf("please pass input path");
		exit(1);
	}
	// step 2: make sure that we are access to the file target
	if(access(argv[1],F_OK) != 0)
	{
		printf("input path doesn't exist");
		exit(1);
	}
	if(access(argv[1],R_OK) != 0)
	{
		printf("the path passed has not read access");
		exit(1);
	}
	// open read stream to the file belong to path
	printf("%s\n",argv[1]);
	input = fopen(argv[1],"r");
	// fetch each char file content
	char digit;
	// digit = fgetc(input);
	while ((digit = fgetc(input)) != EOF) {
		char first = 'm';
		char second = 'u';
		char third = 'r';

		char ufirst = 'M';
                char usecond = 'U';
                char uthird = 'R';
		// function used to read the contents of file
		printf("%c\n",digit);
		// string recognition
        	//if((strcmp(digit, first) == 0) || (strcmp(digit,ufirst)==0))
		if(digit == first || digit == ufirst)
		{
			printf("yes for m, %d",step+1);
			if(step == -1) // store found of first caracter
				step++;
		}
		//else if((strcmp(digit, second) == 0) || (strcmp(digit,usecond)==0))
		else if(digit == second || digit == usecond)
		{
			printf("yes for u, %d",step+1);
			if(step == 0) // recognize the next caracter if the first was already seen 
				step++;
		}
		//else if((strcmp(digit, third) == 0) || (strcmp(digit,uthird)==0))
		else if(digit == third || digit == uthird)
		{
			printf("yes for r, %d",step+1);
			if(step == 1) // recognize the last character if the second was already seen
				step++;
			if(step == 2) // reset the step counter and increment string recognize counter
			{
				counter++;
				step = -1;
			}
		}
		else
		{
			step = -1; // reset step if each other character is found
		}
		// digit = fgetc(input);
    	}
	// close read stream
    	fclose(input);
	// print the end state of our recognize program
	printf("the number of occurence of string ..mur.. is %d",counter);
	
	return 0;
}


// functions declaration

