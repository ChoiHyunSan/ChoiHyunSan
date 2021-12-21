#include <iostream>
#include <string>

using namespace std;

#define SONGS_SIZE 3

float Recursive1(float n) // 문제 1번, 재귀함수를 이용한 프로그램 작성
{
    static float sum = 0;
    if (n > 0) {
        sum += 1 / n;
        n--;
    }
    if (n == 0)
        return sum;
    return Recursive1(n);
}
int sum(int n) // 문제 2번, 재귀함수를 반복함수로 변환하여 작성
{
    int sum = 0;
    for (int i = n; n > 0; n--)
    {
        sum += n;
    }
    return sum;
}
struct Song
{
    char artist[20];
    char title[20];
};
struct Playlist  //플레이리스트 구조체
{
    int num_of_songs = SONGS_SIZE;
    struct Song song[SONGS_SIZE] = {};

    void printlist()  // 플레이 리스트 출력하기
    {
        cout << "NO" << "      Artist       " << "      Title" << endl;
        cout << "==" << "      ======       " << "      =====" << endl;
        for (int i = 1; i <= num_of_songs; i++)
        {
            cout << i << "       " << song[i - 1].artist << song[i - 1].title << endl;
        }
    }
    void cleaning()  // 출력 시, 정렬되어 출력되게끔 공백채워넣기
    {
        for (int i = 0; i < num_of_songs; i++) {  //플레이리스트 안의 노래 개수만큼 반복
            for (int j = strlen(song[i].artist); j < sizeof(song[i].artist); j++)  // 남는공간(전체 - 입력받은공간)을 공백으로 채우기
            {
                song[i].artist[j] = ' ';
            }
            for (int j = strlen(song[i].title); j < sizeof(song[i].title); j++) // 남는공간(전체 - 입력받은공간)을 공백으로 채우기
            {
                song[i].title[j] = ' ';
            }
            song[i].artist[19] = '\0';
            song[i].title[19] = '\0';
        }
    }
};
void StartPlaylist()  // 3번 문제, 플레이 리스트에 가수와 곡을 입력받고 출력하기
{

    struct Playlist playlist;  //플레이리스트 생성

    for (int i = 0; i < playlist.num_of_songs; i++)  //가수명, 곡 입력받기
    {
        char s1[20];
        cout << i + 1 << "번째 가수 명을 입력하시오 : ";
        cin.getline(s1, sizeof(s1), '\n');
        strcpy_s(playlist.song[i].artist, s1);
        cout << i + 1 << "번째 곡 명을 입력하시오 : ";
        cin.getline(s1, sizeof(s1), '\n');
        strcpy_s(playlist.song[i].title, s1);

        cout << endl;

    }
    //정리 및 출력
    playlist.cleaning();
    playlist.printlist();
}
int main()
{
    cout << Recursive1(3) << endl;  //1번문제 실행
    cout << sum(5) << endl;         //2번문제 실행

    StartPlaylist();                //3번문제 실행

}