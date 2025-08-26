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

int evaluation(char postfix[]){
	int i=0;
	char symbol;
	while(postfix[i]!='\0'){
		symbol=postfix[i];
		if(symbol=='+'||symbol=='-'||symbol=='*'||symbol=='/'){
			int a=pop()-'0';
			int b=pop()-'0';
			switch(symbol){
				char res;
				case '+':
					 res=(a+b)+'0';
					push(res);
					break;
				case '-':
					 res=(b-a)+'0';
					push(res);
					break;
				case '*':
					 res=(b*a)+'0';
					push(res);
					break;
				default:
					 res=(b/a)+'0';
					push(res);
			}
		}
		else push(symbol);
		i++;
	}
	return pop()-'0';
}

int main(){
	char infix[100];
	printf("enter the infix expression: ");
	scanf("%s",&infix);
	char postfix[100];
	printf("infix: %s\n",infix);
	infixToPostfix(infix,postfix);
	printf("postfix: %s\n",postfix);
	int res=evaluation(postfix);
	printf("result of this expression %d ",res);
	
	return 0;
}
