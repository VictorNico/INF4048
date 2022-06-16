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
	//printf("the length of %s is %ld and length of %c is %ld\n",word,strlen(word),word[0],sizeof(word[0]));
	printf("the length of word %s is %ld\n",word,length);
	while ((digit = fgetc(input)) != EOF) {
		// function used to read the contents of file
		printf("%c\n",digit);
		// string recognition
        	for(int i = 0; i<length;i++)
		{
			if(digit == word[i] && step == i-1)
				step++;
		}
		if(step == length-1)
		{
			counter++;
			step = -1;
		}

    	}
	// close read stream
    	fclose(input);
	// print the end state of our recognize program
	printf("the number of occurence of string ..%s.. is %d",word,counter);
	
	return 0;
}


// functions declaration

