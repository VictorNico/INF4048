%{
int error = 0;
int state = 0;
int finalError = 0;
%}

%option noyywrap

%%
[0-9]+ {error = 0;state = 0;fprintf(yyout,"<int:%s>",yytext);}
[+-/*=] {error = (state == 1?1:0);finalError = (error ==1?1:finalError);state = (state == 0?1:++state);error == 0?fprintf(yyout,"<operateur:%s>",yytext):fprintf(yyout,"<bad_operateur:%s>",yytext);}
[_a-zA-Z]* {error = 1;fprintf(yyout,"<error:%s>",yytext);}

%%

int main(int argc, char* argv[])
{
	extern FILE *yyin,*yyout;
	yyin = fopen(argv[1],"r");
	yyout = fopen("output.txt","w");
	yylex();
	if(finalError == 1)
	{
		fprintf(yyout,"\nInvalid arithmetical operation in %s\n",argv[1]);
	}
	else
	{
		fprintf(yyout,"\nCorrect arithmetical operation in %s\n",argv[1]);
	}
	printf("\nRecognition end with success\n");
	return 0;

}
