// topic: c program for arithmetic lexical parser using automaton logic

// libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// types, constance declarations
#define init_final_q0 0
#define final_q1 1
#define final_q2 2
#define final_q3 3
#define q4 4

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
	int currentState = init_final_q0;
	// automaton logic
	// init states = {init_final_q0}
	// finite states = {init_final_q0,final_q1,final_q2,final_q3}
	// states = {init_final_q0,final_q1,final_q2,final_q3, q4}
	// alphabet = {a-c}
	// transition function
	// init_final_q0:{
	// 	a->final_q1,
	// 	b->final_q2,
	// 	c->final_q3,
	//	*\{a|b|c}->q4
	// }
	// final_q1:{
	// 	b->final_q2,
	// 	c->final_q3,
	// 	a->final_q1,
	// 	*\{a}->q4
	// }
	// final_q2:{
	// 	b->final_q2,
	// 	a->final_q1,
	// 	c->final_q3
	//	*\{b}->q4
	// }
	// final_q3:{
	// 	a->final_q1,
	// 	b->final_q2,
	// 	c->final_q3,
	// 	*\{c}->q4
	// }
	// q4:{
	// 	a->final_q1,
	// 	b->final_q2,
	// 	c->final_q3,
	// 	*\{a|b|c}->q4
	// }
	// 	
	//
	char* words = calloc(100,sizeof(char));
	int index = 0;	
	while ((digit = fgetc(input)) != EOF) {
		// function used to read the contents of file
		//printf("%c\n",digit);
		// string recognition
		if(currentState == init_final_q0)
		{
			switch(digit)
			{
				case 'a':
					currentState = final_q1;
					words[index++] = digit;
					break;
				case 'b':
					currentState = final_q2;
					words[index++] = digit;
					break;
				case 'c':
					currentState = final_q3;
					words[index++] = digit;
					break;
				default:
					currentState = q4;
					break;
			}
		}
		else if(currentState == final_q1)
		{
			switch(digit)
			{
				case 'a':
					currentState = final_q1;
					words[index++] = digit;
					break;
				case 'b':
					currentState = final_q2;
					words[index++] = digit;
					break;
				case 'c':
					currentState = final_q3;
					words[index++] = digit;
					break;
				default:
					counter++;
					printf("%s\n",words);
					index = 0;
					free(words);
					words =  calloc(100,sizeof(char));
					currentState = q4;
					break;
			}
		}
                else if(currentState == final_q2)
                {
                        switch(digit)
                        {
                              	case 'a':
                                        currentState = final_q1;
					words[index++] = digit;
                                        break;
                                case 'b':
                                        currentState = final_q2;
					words[index++] = digit;
                                        break;
                                case 'c':
                                        currentState = final_q3;
					words[index++] = digit;
                                        break;
                                default:
                                        counter++;
					printf("%s\n",words);
                                        index = 0;
                                        free(words);
                                        words =  calloc(100,sizeof(char));
                                        currentState = q4;
                                        break;
                        }
                }
                else if(currentState == final_q3)
                {
                        switch(digit)
                        {
                                case 'a':
                                        currentState = final_q1;
					words[index++] = digit;
                                        break;
                                case 'b':
                                        currentState = final_q2;
					words[index++] = digit;
                                        break;
                                case 'c':
                                        currentState = final_q3;
					words[index++] = digit;
                                        break;
                                default:
                                        counter++;
					printf("%s\n",words);
                                        index = 0;
                                        free(words);
                                        words =  calloc(100,sizeof(char));
                                        currentState = q4;
                                        break;
                        }
                }
                else if(currentState == q4)
                {
                        switch(digit)
                        {
                                case 'a':
					currentState = final_q1;
					words[index++] = digit;
					break;
                                case 'b':
					currentState = final_q2;
					words[index++] = digit;
					break;
                                case 'c':
                                        currentState = final_q3;
					words[index++] = digit;
                                        break;
                                default:
                                        currentState = q4;
                                        break;
                        }
                }
    	}
	// close read stream
    	fclose(input);
	// print the end state of our recognize program
	printf("%d\n",counter);
	return 0;
}


// functions declaration

