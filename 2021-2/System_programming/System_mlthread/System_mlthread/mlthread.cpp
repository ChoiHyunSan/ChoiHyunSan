#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <tchar.h>
#include <iostream>

#define NUM_OF_THREAD 5

HANDLE hMutex; //뮤택스 생성

// 전역변수 Average, Sum, ParamThread 선언
static float Average = 0;
static float Sum = 0;
float paramThread[12] = {};

/// < 코드 설명 >
/// 1. 입력을 받는 쓰레드( hThread[0] )를 Resume한 이후에 WaitForSingleObject를 통해 입력이 완료 될 때까지 대기
/// 2. 입력이 완료되면 합계평균 쓰레드( hThread[1] ~ hThread[3] )을 Resume 시켜서 합계, 평균을 계산
/// 3. 합계평균을 모두 구할때까지 WaitForMultiObject를 통해 대기한 후, 출력 쓰레드( hThread[4] )를 Resume시켜 결과를 출력
///
/// < 오류 & 작업 중인 내용 >
/// * 쓰레드 동작 함수들 안에 Mutex를 이용하여 입력, 계산 등 서로의 작업에 영향을 주지 않게끔 설정. ( ex. 입력을 받는동안 합계나 출력을 실행하지 않는다. )
/// * 쓰레드가 실행되는 순서가 디버깅을 할 때마다 달라져서 입력쓰레드가 먼저 실행이 되면 정상적으로 작동하지만 나머지의 경우 오류값이 출력. 
///   - WaiForSingleObject와 WaitForMultiObject함수를 통해 실행 순서에 의한 오류 수정.
/// 
/// * WaitForSingleObject, WaitForMultiObject 함수를 사용하지 않고 제어하기 위해서는 초기 Mutex Key값을 가지는 쓰레드를 hThread[0]로 변경하는 것이 필요.

void cal(LPVOID lpParam)  //합계평균 계산함수
{
	int i = (int)lpParam;
	for (int j = i; j < i + 4; j++)
	{
		Sum += paramThread[j];
		//std::cout << paramThread[j]; //합계가 더해지는것을 확인하기 위한 출력
		Average += paramThread[j] / 12;
	}
}
DWORD WINAPI InputThread(LPVOID lpParam) //입력받는 쓰레드 함수
{
	WaitForSingleObject(hMutex, INFINITE);
	printf("숫자 12개를 입력하시오 \n");
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
DWORD WINAPI Sum_AveThread(LPVOID lpParam) //합계와 평균을 구하는 쓰레드 함수
{
	//WaitForSingleObject(hMutex, INFINITE);

	cal(lpParam);  // 계산을 위한 함수 호출
	//std::cout << "+" ; // 하나의 합계평균 쓰레드가 작업을 마쳤음을 알리는 출력

	//ReleaseMutex(hMutex);
	return 0;
}
DWORD WINAPI PrintThread(LPVOID lpParam) //출력하는 쓰레드 함수
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
		NULL,     // 디폴트 보안관리자.
		FALSE,    // 누구나 소유 할 수 있는 상태로 생성.
		NULL      // numaned mutex
	);

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error: %d\n"), GetLastError());
	}

	//쓰레드 생성 : 0-> 입력쓰레드 , 123 -> 합계평균 쓰레드, 4 -> 출력 쓰레드
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

	//입력쓰레드 먼저 실행
	ResumeThread(hThread[0]);
	WaitForSingleObject(hThread[0], INFINITE);

	//평균 합계 쓰레드 3개 동시 실행
	for (DWORD i = 1; i < 4; i++)
	{
		ResumeThread(hThread[i]);
	}
	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	//출력 쓰레드 실행
	ResumeThread(hThread[4]);	
	WaitForSingleObject(hThread[4], INFINITE);

	for (DWORD i = 0; i < NUM_OF_THREAD; i++)
	{
		CloseHandle(hThread[i]);
	}
	CloseHandle(hMutex);

	return 0;
}
