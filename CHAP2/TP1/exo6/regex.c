// topic: c program for arithmetic lexical parser using automaton logic

// libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// types, constance declarations
#define init_q0 0
#define q1 1
#define q2 2
#define final_q3 3
#define error_q4 4

// functions prototypes



// main function declaration
int main(int argc,char *argv[])
{
	// main variables declarations
	int counter = 0; // variable which contains the occurences of mur
	//int step = -1; // variable which indicate at which string recognize level we are
	FILE *input; // variable which reference the file I/O stream content

	// resolution process
	// step 1: make sure that the input patch is not empty
	char** param = argv;
	//printf("size of parameter %d",argc);
	if(argc < 1)
	{
		printf("\nplease pass input path\n");
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
	int currentState = init_q0;
	// automaton logic
	// init states = {init_q0}
	// finite states = {final_q3}
	// states = {init_q0,q1,q2,final_q3,error_q4}
	// alphabet = {a-z,A-z,.,0-9,+,*,-,/}
	// transition function
	// init_q0:{
	// 	*\{i}->error_q4,
	// 	{i}->q1
	// }
	// q1:{
	// 	*\{f}->error_q5,
	// 	{f}->q2
	// }
	// q2:{
	// 	*\{n}->final_q3,
	// 	*->q2
	// }
	// q3:{
	// 	*\{\n}->error_q4,
	// 	\n->init_q0
	// }
	// error_q4:{
	// 	*->error_q4
	// }
	// 	
	//
	
	while ((digit = fgetc(input)) != EOF) {
		// function used to read the contents of file
		//printf("%c\n",digit);
		// string recognition
		if(currentState == init_q0)
		{
			switch(digit)
			{
				case '\0':
				case '\n':
				case EOF:
					currentState = init_q0;
					break;
				case 'i':
					currentState = q1;
					break;
				default:
					currentState = error_q4;
					break;
			}
		}
		else if(currentState == q1)
		{
			switch(digit)
			{
				case '\0':
				case '\n':
				case EOF:
					currentState = init_q0;
					break;
				case 'f':
					currentState = q2;
					break;
				default:
					currentState = error_q4;
					break;
			}
		}
		else if(currentState == q2)
		{
			switch(digit)
			{
				case '\0':
				case '\n':
				case EOF:
					currentState = init_q0;
					break;
				case 'n':
					currentState = final_q3;
					counter++;
					break;
				default:
					currentState = q2;
					break;
			}
		}
		else if(currentState == final_q3)
		{
			switch(digit)
			{
				case '\0':
				case '\n':
				case EOF:
					currentState = init_q0;
					break;
				default:
					currentState = error_q4;
					break;
			}
		}
		else if(currentState == error_q4)
		{
			switch(digit)
			{
				case '\n':
					currentState = init_q0;
					break;
				default:
					currentState = error_q4;
					break;
			}
		}
		// printf("\nmust be on q2\n");
    	}
	// close read stream
    	fclose(input);
	// print the end state of our recognize program
	printf("%d\n",counter);
	return 0;
}


// functions declaration

