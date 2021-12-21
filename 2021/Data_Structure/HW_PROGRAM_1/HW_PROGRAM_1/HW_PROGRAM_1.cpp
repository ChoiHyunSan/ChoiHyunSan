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
		fprintf(stderr, "������ ����á���ϴ�. \n");
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
		fprintf(stderr, "������ ����ֽ��ϴ�. \n");
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

//FALSE ��ȯ���� 1. ��ȣ �� �޺κ��� ���� ���(' ] , } , )') pop���� ¦�� ���� �ʰų� ����ִ� ���. 
//FALSE ��ȯ���� 2. �ݺ����� ������ ���ÿ� ���� �����ִ� ���
int checking(const char* in)
{
	StackType s;
	char ch, open_ch;
	int i;
	int n = strlen(in);

	init_stack(&s);

	for (i = 0; i < n; i++)
	{
		//�ݺ����� ���� ��ȣ�� ��Ī���Ѽ� FALSE ��ȯ���� 1�� check.
		if (matching(&s, in, i) == FALSE)
			return FALSE;
	}
	//FALSE ��ȯ���� 2 check.
	if (!is_empty(&s))
		return FALSE;

	return TRUE;
}
int main()
{
	//�׽�Ʈ�� ���ؼ� 5ȸ	�ݺ����� ����
	int n = 5;
	while (n) {
		char p[MAX_SIZE];
		std::cout << "���� �Է��Ͻÿ� :";
		std::cin >> p;

		if (checking(p) == TRUE)
			printf("YES \n");
		else
			printf("NO \n");
		n--;
	}
	return 0;
}