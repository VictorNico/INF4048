%{
int counter = 0;
char *word;
%}

%option noyywrap

%%
[_a-zA-Z0-9]*(word)[_a-zA-Z0-9]* {counter++;fprintf(yyout,"\noccurence %d = %s\n\n",counter,yytext);}


%%

int main(int argc, char* argv[])
{
	extern FILE *yyin,*yyout;
	yyin = fopen(argv[1],"r");
	yyout = fopen("output.txt","w");
	word = argv[2];
	yylex();
	fprintf(yyout,"le fichier %s contient %d occurence(s) du mot %s\n",argv[1],counter,argv[2]);
	printf("\nRecognition end with success\n");
	return 0;

}
