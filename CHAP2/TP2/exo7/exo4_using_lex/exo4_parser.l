%{
int error = 0;
int state = 0;
%}

%option noyywrap

%%
[0-9]+ {state = 0;fprintf(yyout,"<int:%s>",yytext);}
[+-/*] {state = (state == 0?1:state);error = (state != 0?1:error);fprintf(yyout,"<operateur:%s>",yytext);}
[^([0-9]+)|([+-/*])] {error = 1;fprintf(yyout,"<error:%s>",yytext);}

%%

int main(int argc, char* argv[])
{
	extern FILE *yyin,*yyout;
	yyin = fopen(argv[1],"r");
	yyout = fopen("output.txt","w");
	yylex();
	if(error == 1)
	{
		fprintf(yyout,"\nInvalid arithmetical operation in %s",argv[1]);
	}
	else
	{
		fprintf(yyout,"\nCorrect arithmetical operation in %s",argv[1]);
	}
	printf("\nRecognition end with success\n");
	return 0;

}
