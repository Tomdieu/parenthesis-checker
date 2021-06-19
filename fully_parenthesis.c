#include<stdlib.h>
#include<stdio.h>

typedef struct stack
{
	char value;
	struct stack *next;
}*stack;

typedef enum 
{
	false,
	true
}bool;

#define or ||
#define and &&

stack new()
{
	return NULL;
}


bool isempty(stack st)
{
	if(st == NULL)
		return true;
	return false;
}

stack push(stack st,char x)
{
	stack e;
	e = malloc(sizeof(*e));
	if(e == NULL)
	{
		exit(0);
	}

	e->value = x;
	e->next = NULL;
	if(isempty(st))
		return e;
	e->next = st;
	return e;
}

stack pop(stack st)
{
	if(isempty(st))
	{
		printf("The stack is empty!\n");
	}
	else
	{
		stack tmp = st;
		st = tmp->next;
		free(tmp);
		return st;
	}
}

char top(stack st)
{
	if(isempty(st))
		printf("Top is NULL\n");
	else
		return st->value;
}

void print(stack st)//This function is not so usefull but i have insert it to visualise the poping
{
	if(isempty(st))
	{
		printf("The Stack is Empty\n");
	}
	else
	{
		while(st != NULL)
		{
			printf("%c ", st->value);
			st = st->next;
		}
	}
	printf("\n");
}



int len(char *string){
	int l=0;
	while(*(string++) != '\0')l++;
	return l;
}

int findopen(char x)
{
	if(x == '{' or x == '[' or x=='(')
		return 1;
	return 0;
}

int findclose(char x)
{
	if(x == '}' or x == ']' or x==')')
		return 1;
	return 0;
}

char opposite(char x)
{
	if(x == '}')
		return '{';
	else if (x == ']')
		return '[';
	else if (x == ')')
		return '(';
}

int checker(char *string)
{

	/*
	*	here, the logic is simple if you find either (,{, or [ when traversing
	*	the string you push it to the stack if you find the other that is ],}, or )
	*	when traversing if may be you see } and that the top of the stack is {
	*	then pop and so on an at the end if the stack is empty the expression is valid
	*	else it is not.
	*/
	int i;
	stack st = new();
	for(i = 0;i < len(string); i++)
	{
		if(findopen(string[i]))
		{
			st = push(st,string[i]);
		}
		else if (findclose(string[i]))
		{
			if(opposite(string[i]) == top(st))
			{
				st = pop(st);
			}
			else if (isempty(st))
			{
				return false;
			}
		}
		else if(findclose(string[i]) and isempty(st))
		{
			return false;
		}
	}

	if(isempty(st))
		return true;
	return false;
}


int main(int argc, char const *argv[])
{
	
	char str[100];
	char *s = "Hello World";
	printf("%d\n", *s);
	printf("Enter an expression to determine if it is well form : ");
	fgets(str,100,stdin);
	
	if(checker(str))
	{
		printf("L'expression est valid \n");
	}
	else
	{
		printf("L'expression n'est pas valid\n");
	}
	return 0;
}