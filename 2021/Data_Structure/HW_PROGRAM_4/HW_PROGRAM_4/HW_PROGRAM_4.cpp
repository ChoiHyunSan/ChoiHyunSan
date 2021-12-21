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
	if (is_empty_(s)) {
		fprintf(stderr, "������ ����ֽ��ϴ�. \n");
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
// N/0�� ���� ����ó��
//�Ҽ��� 2�ڸ����� ���

float calculate(char* str)
{
	//���� ����
	StackType s;
	
	//���� �ʱ�ȭ
	init_stack(&s);

	//���� index ���� �а� operand -> push, oprators -> stack-pop ���.

	float op1,op2,result(0);
	int set = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		float temp = result;
		switch (str[i]) {
			// '+,-,*�� ��� pop�� �ؼ� ���'
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
			// '/'�� op2�� 0�ΰ�� ����ó��
			case '/':
			{
				op1 = pop(&s);
				op2 = pop(&s);
				if (op1 == 0) {
					cout << "�߸��� �����Դϴ�.";
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

	//���� �ϳ��� �Էµ� ���
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

		//�� �Է¹ޱ�
		cout << "���� �Է����ּ���";
		cin >> str;

		//�� ����ؼ� result�� ��ȯ
		float result = calculate(str);

		printf("�Է��� ���� ���� %.2f�Դϴ� \n", result);
	}
	return 0;
}