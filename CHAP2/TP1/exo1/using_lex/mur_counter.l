%{
int counter = 0;
%}

%option noyywrap

%%
[_a-zA-Z0-9]*mur[_a-zA-Z0-9]* {counter++;fprintf(yyout,"\noccurence %d = %s\n\n",counter,yytext);}

%%

int main(int argc, char* argv[])
{
	extern FILE *yyin,*yyout;
	yyin = fopen(argv[1],"r");
	yyout = fopen("output.txt","w");
	yylex();
	fprintf(yyout,"le fichier %s contient %d occurence(s) du mot mur\n",argv[1],counter);
	printf("\nRecognition end with success\n");
	return 0;

}
