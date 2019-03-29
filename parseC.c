#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void parseNumber()
{
	int c;
	while (isdigit((c = getc(stdin)))) 
		printf("%c", c);
	ungetc (c, stdin);
}

void parseWord()
{
	int c;
	while (isalnum((c = getc(stdin))) || c == '_')
		printf("%c", c);
	ungetc (c, stdin);
}

//-----------------------------------------------------------------------

void charLiteral()
{
	int c;
	while ((c = getc(stdin)) != '\'')
		printf("%c", c);
	printf("%c", c);
}

void stringLiteral()
{
	int c;
	while ((c = getc(stdin)) != '\"')
		printf("%c", c);
	printf("%c", c);
}

//-----------------------------------------------------------------------

int endOfComment()
{
	int c = getc(stdin);
	printf("%c", c);
	if (c == '/') return 1;
	return 0;
}

void comment()
{
	int c;
	while ((c = getc(stdin)))
	{
		printf("%c",c);
		if (c == '*' && endOfComment())
			break;
	}
}

//-----------------------------------------------------------------------

void tokenize(int c)
{
	switch (c)
	{
  		case ' ':case'\t':case'\n': 
			break;

		case'\'':
			printf("\n%c", c);			
			charLiteral();
			break;

		case'\"':
			printf("\n%c", c);			
			stringLiteral();
			break;
	
		case'/':
			printf("\n%c", c);
			if((c = getc(stdin)) == '*')
					printf("%c",c), comment();
			else ungetc(c,stdin);
			break;

		case '+':
			printf("\n%c", c);
			(c = getc(stdin)) == '+' ? printf("%c", c) : ungetc (c,stdin);
			break;
		
		case '-':
			printf("\n%c", c);
			(c = getc(stdin)) == '-' ? printf("%c", c) : ungetc (c,stdin);
			break;

		case '&':
			printf("\n%c", c);
			(c = getc(stdin)) == '&' ? printf("%c", c) : ungetc (c,stdin);
			break;
			
		case '|':
			printf("\n%c", c);
			(c = getc(stdin)) == '|' ? printf("%c", c) : ungetc (c,stdin);
			break;
						

		case'<': case'>':case'*':case'=':case'^':
		case'%':case'!':case'?':case'~':case'#': 
			printf("\n%c",c); 
			break;
	
		default:
			printf("\n%c", c);
			if (isdigit(c)) parseNumber();
			else if (isalpha(c)) parseWord();
			break;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	char c;
	while ((c = getc(stdin)) != EOF)
		tokenize(c);
	printf("\n");

	return 0;
}
