// OperatingSys.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>

int main()
{
	printf("Hello World! \n");

	int number;

	while (true) {
		printf("Enter number: ");
		scanf_s("%d", &number);

		switch (number)
		{
		case 1:
			printf("1 \n");
			break;
		case 2:
			printf("2 \n");
			break;
		default:
			printf("error \n");
			break;
		}
	}
}

