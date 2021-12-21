#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctype.h>

#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

using namespace std;

//회문인지 판독하는 함수
//입력받은 문자열을 모두 소문자로 바꾸기
//공백문자 , 특수문자는 스택에 넣지 않는다.

typedef char element;
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
element peek(StackType* s)
{
	if (is_empty_(s))
	{
		fprintf(stderr, "스택이 비어있습니다. \n");
		exit(1);
	}
	return s->data[s->top];
}

//입력받은 문장에서 대문자는 소문자로 변환한다.
void is_BigLetter(char* p)
{
	for (int i = 0; i < (int)strlen(p); p++)
	{
		if (p[i] == toupper(p[i])) {
			p[i] = tolower(p[i]);
		}
	}
}
//나의 생각 : 알파벳들을 모두 스택에 push하고, pop으로 꺼내게 되면 뒤에서부터 꺼내지므로 문장에 반대로 뒤집어진다.
//           그러므로 push되어 들어가있는 문장이 pop으로 꺼내져서 나온 문장과 같다면 TRUE일 것이다.
int is_Palindrome(char* p)
{
	StackType s;	
	//char str[MAX_SIZE];
	is_BigLetter(p);
	int count = 0;


	init_stack(&s);  // 스택 초기화

	for (int i = 0; i < (int)strlen(p); p++) {//총 문장에서
			if (isalpha(p[i])!=0) { // 알파벳이면
				push(&s, p[i]);	//스택에 push한다.
				count++;
			}
	}

	char str[MAX_SIZE];

	for (int i = 0; i < count; i++)
	{
		str[i] = pop(&s); //pop시킨 문자들을 순서대로 str에 저장
	}
	str[count] = '\0';
	s.data[count] = '\0';

	cout <<"sentence : "<< str << endl; 
	cout <<"reverse : "<< s.data << endl;
	if (!strcmp(str,s.data))
		return TRUE;
	else
		return FALSE;
}

int main()
{
	char p[MAX_SIZE];
	printf("문장을 입력하시오 :");
	std::cin.getline(p,MAX_SIZE);

	if (is_Palindrome(p) == TRUE)
		cout << "Yes";
	else
		cout << "NO";

	
}