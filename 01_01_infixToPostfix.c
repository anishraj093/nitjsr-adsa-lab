#include <stdio.h>
#include <string.h>

char stack[100];
int top=-1;

void push(char c){
	stack[++top]=c;
}
char pop(){
	return stack[top--];
}

int precedence(char c){
	if(c=='+'||c=='-')return 1;
	else if(c=='*'||c=='/') return 2;
	else return 0;
}

void infixToPostfix(char infix[],char postfix[]){
	int i=0,j=0;
	push('(');
	strcat(infix,")");
	char symbol;
	
	while(infix[i]!='\0'){
		symbol=infix[i];
		if(symbol=='(')push(symbol);
		else if(symbol==')'){
			while(top!=-1&&stack[top]!='('){
				postfix[j++]=pop();
			}
			pop();
		}
		else if(symbol=='+'||symbol=='-'||symbol=='*'||symbol=='/'){
			while(top!=-1&&precedence(symbol)<=precedence(stack[top]))postfix[j++]=pop();
			push(symbol);
		}
		else postfix[j++]=symbol;
		i++;
	}
	postfix[j]='\0';
}


int main(){
	char infix[100];
	printf("enter the infix expression: ");
	scanf("%s",&infix);
	char postfix[100];
	printf("infix: %s\n",infix);
	infixToPostfix(infix,postfix);
	printf("postfix: %s\n",postfix);
	
	
	return 0;
}
