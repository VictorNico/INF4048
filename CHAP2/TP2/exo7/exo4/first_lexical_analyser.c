// topic: c program for arithmetic lexical parser using automaton logic

// libraries importation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// types, constance declarations
#define init_q0 0
#define q1 1
#define final_q2 2
#define q3 3
#define final_q4 4
#define error_q5 5

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
	char* reader = calloc(10,sizeof(char));
	char* all = calloc(100,sizeof(char));
	int i = 0;
	// fetch each char file content
	char digit;
	int currentState = init_q0;
	// automaton logic
	// init states = {init_q0}
	// finite states = {final_q2,final_q4}
	// states = {init_q0,q1,final_q2,q3,final_q4,error_q5}
	// alphabet = {0-9,+,*,-,/}
	// transition function
	// init_q0:{
	// 	{0-9}->init_q0,
	// 	{+,*,-,/}->q1
	// }
	// q1:{
	// 	{+,-,*,/}->error_q5,
	// 	{0-9}->final_q2
	// }
	// final_q2:{
	// 	{0-9}->final_q2,
	// 	{+,*,-,/}->q3
	// }
	// q3:{
	// 	{+,*,-,/}->error_q5,
	// 	{0-9}->final_q5
	// }
	// final_q4:{
	// 	{0-9}->final_q2,
	// 	{*,+,-,/}->q3
	// }
	// error_q5:{
	// 	{0-9,+,*,-,/}->error_q5
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
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					currentState = init_q0;
					reader[counter] = digit;
					all[i] = digit;
					counter++;
					i++;
					break;
				case '+':
				case '*':
				case '-':
				case '/':
					currentState = q1;
					all[i] = digit;
					printf("<int:%s><operator:%c>",reader,digit);
					i++;
					counter = 0;
					free(reader);
					reader = calloc(10,sizeof(char));
					break;
				default:
					currentState = error_q5;
					all[i] = digit;
					i++;
					break;
			}
		}
		else if(currentState == q1)
		{
			switch(digit)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					currentState = final_q2;
					reader[counter] = digit;
					all[i] = digit;
					counter++;
					i++;
					break;
				default:
					currentState = error_q5;
					all[i] = digit;
					i++;
					break;
			}
		}
		else if(currentState == final_q2)
		{
			switch(digit)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					currentState = final_q2;
					reader[counter] = digit;
					all[i] = digit;
					counter++;
					i++;
					break;
				case '+':
				case '*':
				case '-':
				case '/':
					currentState = q3;
					all[i] = digit;
					printf("<int:%s><operator:%c>",reader,digit);
					i++;
					counter = 0;
					free(reader);
					reader = calloc(10,sizeof(char));
					break;
				default:
					currentState = error_q5;
					all[i] = digit;
					i++;
					break;
			}
		}
		else if(currentState == q3)
		{
			switch(digit)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					currentState = final_q4;
					reader[counter] = digit;
					all[i] = digit;
					counter++;
					i++;
					break;
				default:
					currentState = error_q5;
					all[i] = digit;
					i++;
					break;
			}
		}
		else if(currentState == final_q4)
		{
			switch(digit)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					currentState = final_q2;
					reader[counter] = digit;
					all[i] = digit;
					counter++;
					i++;
					break;
				case '+':
				case '*':
				case '-':
				case '/':
					currentState = q3;
					all[i] = digit;
					printf("<int:%s><operator:%c>",reader,digit);
					i++;
					counter = 0;
					free(reader);
					reader = calloc(10,sizeof(char));
					break;
				case EOF:
				case '\n':
				case '\0':
					all[i] = digit;
					break;
				default:
					printf("\nq%d %c %d",currentState,digit,digit=='\n');
					currentState = error_q5;
					all[i] = digit;
					i++;
					break;
			}
		}
		else if(currentState == error_q5)
		{
			switch(digit)
			{
				default:
					currentState = error_q5;
					all[i] = digit;
					i++;
					break;
			}
		}
		// printf("\nmust be on q2\n");
    	}
	// close read stream
    	fclose(input);
	// print the end state of our recognize program
	switch(currentState)
	{
		case 3:
		case 1:
		case 5:
			printf("\nparsing error in arithmetical expression \n\t%s\n",all);
			break;
		default:
			printf("<int:%s>\nparsing end with success for arithmetical expression \n\t%s\n",reader,all);
			break;
	}
	free(reader);
	free(all);
	return 0;
}


// functions declaration

