#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

typedef char element;
typedef struct {
	element data[MAX_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	if (s->top == -1)
		return TRUE;
	else
		return FALSE;
}

int is_full(StackType* s)
{
	if (s->top == (MAX_SIZE - 1))
		return TRUE;
	else
		return FALSE;
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
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
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있습니다. \n");
		exit(1);
	}
	else {
		temp = s->data[s->top];
		(s->top)--;
		return temp;
	}
}

int matching(StackType *s ,const char* in, int i)
{
	char ch, open_ch;
	ch = in[i];
	switch (ch) {
	case '(':
	case '[':
	case '{':
		push(s, ch);
		break;
	case ')':
	case ']':
	case '}':
		if (is_empty(s))
			return FALSE;
		else {
			open_ch = pop(s);

			if ((open_ch == '(' && ch != ')') ||
				(open_ch == '{' && ch != '}') ||
				(open_ch == '[' && ch != ']'))
				return FALSE;
		}
		break;
	}
}

//FALSE 반환조건 1. 괄호 앞 뒷부분이 들어올 경우(' ] , } , )') pop값과 짝이 맞지 않거나 비어있는 경우. 
//FALSE 반환조건 2. 반복문이 끝나고 스택에 값이 남아있는 경우
int checking(const char* in)
{
	StackType s;
	char ch, open_ch;
	int i;
	int n = strlen(in);

	init_stack(&s);

	for (i = 0; i < n; i++)
	{
		//반복문을 통해 괄호를 매칭시켜서 FALSE 반환조건 1을 check.
		if (matching(&s, in, i) == FALSE)
			return FALSE;
	}
	//FALSE 반환조건 2 check.
	if (!is_empty(&s))
		return FALSE;

	return TRUE;
}
int main()
{
	//테스트를 위해서 5회	반복루프 생성
	int n = 5;
	while (n) {
		char p[MAX_SIZE];
		std::cout << "식을 입력하시오 :";
		std::cin >> p;

		if (checking(p) == TRUE)
			printf("YES \n");
		else
			printf("NO \n");
		n--;
	}
	return 0;
}