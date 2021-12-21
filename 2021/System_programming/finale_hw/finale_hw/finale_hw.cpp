/// < 문제 >
/// 전역변수 int g_total = 1000 이 있다.스레드 3개에는 각각 다음과 같은 일을 수행하다. 
/// 즉, 하나의 스레드 1은 g_total 값을 하나씩 감소시키고, 스레드 2는 g_total 값을 1씩 증가시킨다.
/// 스레드 3은 g_total 값을 출력하는 일을 수행한다고 가정한다.
/// 항상 g_total 의 값이 1000보다 큰 값이 유지될 수 있도록 스레드의 동기화된 프로그램을 수행하시오.
/// 단, 동기화객체는 criticalsection, mutex, semophire, event 중에서 사용하시고, 
/// 반복처리를 보여줘야 하며, C / C++언어 사용.


/// 1일차 
/// 1) 진행 상황
/// 뮤텍스를 이용하여 g_total값을 하나의 쓰레드씩 접근할 수 있게끔 설정.
/// 감소 쓰레드를 제어하기 위해서 이벤트를 사용.
/// 
/// 2) 기타 어려운 사항
/// 감소 쓰레드를 통제하는 ResetEvent의 위치를 어디에 두어야 하는지에 대한 어려움이 생김.
/// 
/// 
/// 2일차
/// 1)진행 상황
/// ResetEvent의 위치를 increase_thread에서 decrease_thread로 옮겨서 두 쓰레드가 서로에 관계없이
/// 돌아갈 수 있게끔 하였고, decrease_thread가 실행 될 때마다 Event를 활성화 시킬지에 대한 조건문을 달아서
/// 1000과 같거나 작을 경우 바로 return되게끔 하였다.
/// 
/// 2) 기타사항
/// 쓰레드들이 돌아가는 것을 확인하기 위해 g_total값을 조작 할 때마다 출력문을 통해 동작되는 모습을 확인하였다.
/// 쓰레들은 기본적으로 while(1)을 통하여 무한히 반복하지만, int count를 통해 출력되는 쓰레드가 실행되는 횟수에
/// 따라서 프로그램이 끝난다.





#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
#include <tchar.h>
#include <iostream>


#define NUM_OF_THREAD 3

using namespace std;


HANDLE hMutex; //뮤택스 생성
HANDLE hEvent; //이벤트 생성

int g_total = 1000; // 전역변수 g_total 생성
int count_ = 20; //출력 횟수

DWORD WINAPI decrease_Thread(LPVOID lpParam) { //감소 쓰레드 

	WaitForSingleObject(hMutex, INFINITE);

	if (g_total <= 1000) {
		ResetEvent(hEvent);
		//cout << "1000보다 작거나 같으므로 decrease 쓰레드를 중지합니다" << endl;
		ReleaseMutex(hMutex);
		return 0;
	}
	else {
		//cout << "1000보다 크므로 decrease 쓰레드를 실행합니다" << endl;
		SetEvent(hEvent);
	}

	WaitForSingleObject(hEvent, INFINITE);
	
	g_total--;
	//cout << "g_total 감소" << endl;

	ReleaseMutex(hMutex);

	return 0;
}
DWORD WINAPI increase_Thread(LPVOID lpParam) { //증가 쓰레드
	
	WaitForSingleObject(hMutex, INFINITE);

	g_total++;
	//cout << "g_total 증가" << endl;

	ReleaseMutex(hMutex);

	
	return 0;
}
DWORD WINAPI print_Thread(LPVOID lpParam) { //출력 쓰레드
	
	WaitForSingleObject(hMutex, INFINITE);

	std::cout << g_total << std::endl;
	count_--;

	ReleaseMutex(hMutex);
	
	return 0;
}
int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId[NUM_OF_THREAD];
	HANDLE hThread[NUM_OF_THREAD];

	hEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL
	);

	hMutex = CreateMutex(
		NULL,     // 디폴트 보안관리자.
		FALSE,    // 누구나 소유 할 수 있는 상태로 생성.
		NULL      // numaned mutex
	);

    // Event, Mutex 가 NULL이면 오류처리
	if (hMutex == NULL || hEvent == NULL)
	{
		_tprintf(_T("error: %d\n"), GetLastError());
	}

	while (1) {
		//쓰레드 생성 : [0] -> 감소 쓰레드 , [1] -> 증가 쓰레드 , [2] -> 출력 쓰레드
		hThread[0] =
			CreateThread(
				NULL,
				0,
				decrease_Thread,
				NULL,
				0,
				&dwThreadId[0]
			);
		hThread[1] =
			CreateThread(
				NULL,
				0,
				increase_Thread,
				NULL,
				0,
				&dwThreadId[1]
			);
		hThread[2] =
			CreateThread(
				NULL,
				0,
				print_Thread,
				NULL,
				0,
				&dwThreadId[2]
			);

		// 쓰레드가 NULL이면 오류 처리
		for (DWORD i = 0; i < NUM_OF_THREAD; i++)
		{
			if (hThread[i] == NULL)
			{
				_tprintf(_T("Thread creation fault! \n"));
				return -1;
			}
		}

		//ResetEvent(hEvent);

		if (count_ == 0)
			break;
	}

	
	for (DWORD i = 0; i < NUM_OF_THREAD; i++)
	{
		CloseHandle(hThread[i]);
	}
	

	CloseHandle(hMutex);
	CloseHandle(hEvent);

	return 0;
}

