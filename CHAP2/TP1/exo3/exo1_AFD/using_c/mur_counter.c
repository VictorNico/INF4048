  // topic: program that is able to count the number of occurence of string mur WITHIN E-AFN approach

// libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// types, constance declarations
// automaton state
#define init_q0 0
#define q1 1
#define q2 2
#define final_q3 3
// functions prototypes



// main function declaration
int main(int argc,char *argv[])
{
	// main variables declarations
	int counter = 0; // variable which contains the occurences of mur
	// int step = -1; // variable which indicate at which string recognize level we are
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
	// step 2: make sure that we have access to the target file
	if(access(argv[1],F_OK) != 0)
	{
		printf("input path doesn't exist");
		exit(1);
	}
	if(access(argv[1],R_OK) != 0)
	{
		printf("the file passed has no read access");
		exit(1);
	}
	// open read stream to the file belong to path
	printf("%s\n",argv[1]);
	input = fopen(argv[1],"r");
	// fetch each char file content
	char digit;
	int currentState = init_q0; // automaton current state
	char *code = malloc(1000 * sizeof(char));
	// do
	while(!feof(input))
	{
		digit = fgetc(input);
		*code++ = digit;
		char first = 'm';
		char second = 'u';
		char third = 'r';

		char ufirst = 'M';
                char usecond = 'U';
                char uthird = 'R';
		// function used to read the contents of file
		// printf("%c\n",digit);
		// string recognition E-AFN
		// the transition fonction use is the following
		// init_q0:{
		//	m|M->q1
		// },
		// q1:{
		// 	u|U->q2,
		// 	m|M->q1,
		// 	*\{u|U|m|M}->init_q
		// },
		// q2:{
		// 	r|R->final_q3,
		// 	m|M->q1,
		// 	*\{r|R|m|M}->init_q0
		// },
		// q3:{
		// 	E->init_q0
		// }
		//
		// onto state init_q0
		if(currentState == init_q0)
                {
			// if i see m or M go onto q1
			if(digit == first || digit == ufirst)
	                {
				//printf("%c",digit);
                                currentState = q1; // accept the caracter and go onto state 1

			}
			// not acted if i see anything else
	                
                }
		// onto state q1
              	else if(currentState == q1)
                {
			// if i see u or U go onto q2
                        if(digit == second || digit == usecond)
                        {
				//printf("%c",digit);
                                currentState = q2; // accept the caracter and go onto state 2
                        }
			// else if i see m or M  stay on q1
			else if(digit == first || digit == ufirst)
                        {
                                //printf("%c",digit);
                                currentState = q1; // accept the caracter and go onto state 1

                        }
			// if i see anything else go onto init_q0
                        else
                        {
				//printf("%c",digit);
                                currentState = init_q0; // back onto init state 0
                        }
                }
		// onto q2
		else if(currentState == q2)
                {
			// if i see r or R go onto final_q3
                        if(digit == third || digit == uthird)
                	{
                                //printf("%c",digit);
                                currentState = final_q3; // accept the caracter and go onto the final state 3 
                        }
			// if i see m or M go onto q1
			else if(digit == first || digit == ufirst)
                        {
                                //printf("%c",digit);
                                currentState = q1; // accept the caracter and go onto state 1

                        }
			// if i see anything else go onto init_q0
                        else 
                        {
                                //printf("%c",digit);
                                currentState = init_q0; // back onto init state 0
                        }
               	}
		// check we are onto final state to end recognition and back onto init state
		if(currentState == final_q3)
		{
			counter++;
			currentState = init_q0;
			//printf("%d\n",counter);
		}
    	} 
	//while(digit != EOF);
	// close read stream
    	fclose(input);
	//printf("all the text is:\n\n%s",code);
	// print the end state of our recognize program
	printf("the number of occurence of string ..mur.. is %d\n",counter);
	
	return 0;
}


// functions declaration

