#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <tchar.h>
#include <iostream>

#define NUM_OF_THREAD 5

HANDLE hMutex; //���ý� ����

// �������� Average, Sum, ParamThread ����
static float Average = 0;
static float Sum = 0;
float paramThread[12] = {};

/// < �ڵ� ���� >
/// 1. �Է��� �޴� ������( hThread[0] )�� Resume�� ���Ŀ� WaitForSingleObject�� ���� �Է��� �Ϸ� �� ������ ���
/// 2. �Է��� �Ϸ�Ǹ� �հ���� ������( hThread[1] ~ hThread[3] )�� Resume ���Ѽ� �հ�, ����� ���
/// 3. �հ������ ��� ���Ҷ����� WaitForMultiObject�� ���� ����� ��, ��� ������( hThread[4] )�� Resume���� ����� ���
///
/// < ���� & �۾� ���� ���� >
/// * ������ ���� �Լ��� �ȿ� Mutex�� �̿��Ͽ� �Է�, ��� �� ������ �۾��� ������ ���� �ʰԲ� ����. ( ex. �Է��� �޴µ��� �հ質 ����� �������� �ʴ´�. )
/// * �����尡 ����Ǵ� ������ ������� �� ������ �޶����� �Է¾����尡 ���� ������ �Ǹ� ���������� �۵������� �������� ��� �������� ���. 
///   - WaiForSingleObject�� WaitForMultiObject�Լ��� ���� ���� ������ ���� ���� ����.
/// 
/// * WaitForSingleObject, WaitForMultiObject �Լ��� ������� �ʰ� �����ϱ� ���ؼ��� �ʱ� Mutex Key���� ������ �����带 hThread[0]�� �����ϴ� ���� �ʿ�.

void cal(LPVOID lpParam)  //�հ���� ����Լ�
{
	int i = (int)lpParam;
	for (int j = i; j < i + 4; j++)
	{
		Sum += paramThread[j];
		//std::cout << paramThread[j]; //�հ谡 �������°��� Ȯ���ϱ� ���� ���
		Average += paramThread[j] / 12;
	}
}
DWORD WINAPI InputThread(LPVOID lpParam) //�Է¹޴� ������ �Լ�
{
	WaitForSingleObject(hMutex, INFINITE);
	printf("���� 12���� �Է��Ͻÿ� \n");
	for (int i = 0; i < 12; i++)
	{
		std::cin >> paramThread[i];
	}
	for (int i = 0; i < 12; i++)
	{
		std::cout << paramThread[i] << " ";
	}
	ReleaseMutex(hMutex);
	return 0;
	
}
DWORD WINAPI Sum_AveThread(LPVOID lpParam) //�հ�� ����� ���ϴ� ������ �Լ�
{
	//WaitForSingleObject(hMutex, INFINITE);

	cal(lpParam);  // ����� ���� �Լ� ȣ��
	//std::cout << "+" ; // �ϳ��� �հ���� �����尡 �۾��� �������� �˸��� ���

	//ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI PrintThread(LPVOID lpParam) //����ϴ� ������ �Լ�
{
	WaitForSingleObject(hMutex, INFINITE);
	printf(" \n %f, %f \n", Sum, Average);
	ReleaseMutex(hMutex);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId[NUM_OF_THREAD];
	HANDLE hThread[NUM_OF_THREAD];

	hMutex = CreateMutex(
		NULL,     // ����Ʈ ���Ȱ�����.
		FALSE,    // ������ ���� �� �� �ִ� ���·� ����.
		NULL      // numaned mutex
	);

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error: %d\n"), GetLastError());
	}

	//������ ���� : 0-> �Է¾����� , 123 -> �հ���� ������, 4 -> ��� ������
	hThread[0] =
		CreateThread(
			NULL,
			0,
			InputThread,
			NULL,
			CREATE_SUSPENDED,
			&dwThreadId[0]
		);
	hThread[1] =
		CreateThread(
			NULL,
			0,
			Sum_AveThread,
			(LPVOID)(0),
			CREATE_SUSPENDED,
			&dwThreadId[1]
		);
	hThread[2] =
		CreateThread(
			NULL,
			0,
			Sum_AveThread,
			(LPVOID)(4),
			CREATE_SUSPENDED,
			&dwThreadId[2]
		);
	hThread[3] =
		CreateThread(
			NULL,
			0,
			Sum_AveThread,
			(LPVOID)(8),
			CREATE_SUSPENDED,
			&dwThreadId[3]
		);
	hThread[4] =
		CreateThread(
			NULL,
			0,
			PrintThread,
			NULL,
			CREATE_SUSPENDED,
			&dwThreadId[4]
		);

	for (DWORD i = 0; i < NUM_OF_THREAD; i++)
	{
		if (hThread[i] == NULL)
		{
			_tprintf(_T("Thread creation fault! \n"));
			return -1;
		}
	}

	//�Է¾����� ���� ����
	ResumeThread(hThread[0]);
	WaitForSingleObject(hThread[0], INFINITE);

	//��� �հ� ������ 3�� ���� ����
	for (DWORD i = 1; i < 4; i++)
	{
		ResumeThread(hThread[i]);
	}
	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	//��� ������ ����
	ResumeThread(hThread[4]);	
	WaitForSingleObject(hThread[4], INFINITE);

	for (DWORD i = 0; i < NUM_OF_THREAD; i++)
	{
		CloseHandle(hThread[i]);
	}
	CloseHandle(hMutex);

	return 0;
}
