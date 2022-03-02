#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

using namespace std;

typedef float element;
typedef struct {
	element data[MAX_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty_(StackType* s)
{
	if (s->top == -1)
		return TRUE;
	else
		return FALSE;
}

int is_full_(StackType* s)
{
	if (s->top == (MAX_SIZE - 1))
		return TRUE;
	else
		return FALSE;
}

void push(StackType* s, element item)
{
	if (is_full_(s)) {
		fprintf(stderr, "스택이 가득찼습니다. \n");
		return;
	}
	else {
		(s->top)++;
		s->data[s->top] = item;
	}
}

element pop(StackType* s)
{
	element temp;
	if (is_empty_(s)) {
		fprintf(stderr, "스택이 비어있습니다. \n");
		exit(1);
	}
	else {
		temp = s->data[s->top];
		(s->top)--;
		return temp;
	}
}

//operand = 0~9
//operators = +,-,*,/
// N/0인 경우는 예외처리
//소수점 2자리까지 출력

float calculate(char* str)
{
	//스택 생성
	StackType s;
	
	//스택 초기화
	init_stack(&s);

	//식의 index 값을 읽고 operand -> push, oprators -> stack-pop 계산.

	float op1,op2,result(0);
	int set = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		float temp = result;
		switch (str[i]) {
			// '+,-,*의 경우 pop을 해서 계산'
			case '+':
			case '-': 
			case '*': 
			{
				op1 = pop(&s);
				op2 = pop(&s);
				if (str[i] == '+') 
				{
					result = op1 + op2;
				}
				else if (str[i] == '-')
				{
					result = op1 - op2;
				}
				else
				{
					result = op1 * op2;
				}
				set++;
				push(&s, result);
				break;
			}
			// '/'는 op2가 0인경우 예외처리
			case '/':
			{
				op1 = pop(&s);
				op2 = pop(&s);
				if (op1 == 0) {
					cout << "잘못된 수식입니다.";
					exit(1);
				}
				else
				{
					result = op2 / op1;
				}
				set++;
				push(&s, result);
				break;
			}	
		}
		if(temp==result)
			push(&s, (str[i]-'0'));

	}

	//숫자 하나만 입력될 경우
	if (s.top == 0 && set ==0)
	{
		result = pop(&s);
	}
	return result;
}

int main()
{
	while (1) {
		char str[MAX_SIZE];

		//식 입력받기
		cout << "식을 입력해주세요";
		cin >> str;

		//식 계산해서 result값 반환
		float result = calculate(str);

		printf("입력한 식의 답은 %.2f입니다 \n", result);
	}
	return 0;
}