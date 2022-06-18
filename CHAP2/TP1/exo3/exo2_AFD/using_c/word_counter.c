// topic: program that is able to count the number of occurence of an user string using E-AFN

// libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// types, constance declarations
#define init_q0 0
#define inter_q1 1
#define final_q2 2

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
	printf("size of parameter %d",argc);
	if(argc < 1)
	{
		printf("\nplease pass input path\n");
		exit(1);
	}
	if(argc < 2)
        {
                printf("\nplease pass the word to recognize\n");
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
	char* word = argv[2];
	size_t length = strlen(word);
	int currentState = init_q0;
	//printf("the length of %s is %ld and length of %c is %ld\n",word,strlen(word),word[0],sizeof(word[0]));
	printf("the length of word %s is %ld\n",word,length);
	while ((digit = fgetc(input)) != EOF) {
		// function used to read the contents of file
		//printf("%c\n",digit);
		// string recognition
		if(currentState == init_q0)
		{
			if(digit == word[0])
			{
				//printf("q0,%c->q1\n",digit);
				step++;
				currentState = inter_q1;
			}
		}
		else if(currentState == inter_q1)
		{
			if(step+1 == length-1)
			{
				if(word[step+1] == digit)
				{
					currentState = final_q2;
					//printf("q1,%c on step %d -> q2\n",digit,step);
				}
				else if(word[0] == digit)
				{
					printf("q1,%c->q1\n",digit);
					//step = 0; // mark that we have already recognized the first caracter
				}
				else
				{
					//printf("q1,%c->q0\n",digit);
					step = -1; // back onto first recognition
				}
			}
			else
			{
				if(word[step+1] == digit)
				{
					//printf("q1,%c->q1 on step %d\n",digit,step+1);
					step++; // mark that we have recognized a new caracter
				}
				else if(word[0] == digit)
                                {
					//printf("q1,%c->q1\n",digit);
                                        step = 0; // mark that we have already recognized the first caracter
				}
                                else
                                {
					//printf("q1,%c->q0\n",digit);
                                        step = -1; // back onto first recognition
                                }

			}
		}

		if(currentState == final_q2)
		{
			//printf("\ninside finale state\n");
			currentState = init_q0;
			counter++;
			step = -1;
		}
		// printf("\nmust be on q2\n");
    	}
	// close read stream
    	fclose(input);
	// print the end state of our recognize program
	printf("the number of occurence of string ..%s.. is %d\n",word,counter);
	
	return 0;
}


// functions declaration

