#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1]) {}
	~Screen() { delete[] screen; }

	void draw(int pos, const char* face)
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render()
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class GameObject {
	int pos;
	char face[20];
	Screen* screen;
	bool isLeft;
	int hp;

public:
	GameObject(int pos, const char* face, Screen* screen, int hp)
		: pos(pos), screen(screen), hp(hp)
	{
		strcpy(this->face, face);
	}
	int getPosition()
	{
		return pos;
	}
	void setPosition(int pos)
	{
		this->pos = pos;
	}
	void draw()
	{
		if (hp != 0)
			screen->draw(pos, face);
	}
	void changeLeft()
	{
		isLeft = true;
		strcpy(this->face, "(<_<)");
	}
	void changeRight()
	{
		isLeft = false;
		strcpy(this->face, "(>_>)");
	}
	void changeBullet()
	{
		strcpy(this->face, "*");
	}
	void changeLaser()
	{
		strcpy(this->face, "=");
	}
	bool getIsLeft()
	{
		return isLeft;
	}
	void hpDown(int bullet_pos)
	{
		if (hp == 0)return;
		if (bullet_pos == pos) {
			hp--;
		}
	}
	int getHp()
	{
		return hp;
	}
};

class Player : public GameObject {
	char face[20];
	int pos;
	int hp;
public:
	Player(int pos, const char* face, Screen* screen, int hp)
		: GameObject(pos, face, screen, hp), pos(pos), hp(hp)
	{
		strcpy(this->face, face);
	}
	void moveLeft()
	{
		changeLeft();
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		changeRight();
		setPosition(getPosition() + 1);
	}

	void update(int enemy_pos)
	{

	}

};

class Enemy : public GameObject {
	int pos;
	int hp;
public:
	Enemy(int pos, const char* face, Screen* screen, int hp)
		: GameObject(pos, face, screen, hp), pos(pos), hp(hp)
	{
	}
	void moveForPlayer(int player_pos)
	{
		if (pos == player_pos) return;
		if (pos < player_pos)
			setPosition(getPosition() + 1);
		else if (pos > player_pos)
			setPosition(getPosition() - 1);
		else
			return;
	}
	void update(int player_pos, int GameTime, int bullet_pos)
	{
		GameObject::hpDown(bullet_pos);
		if (GameTime % 5 == 0)
			moveForPlayer(player_pos);

	}
};

class Bullet : public GameObject {
	bool isFiring;
	int weaponType = 1;
	int pos;
	int laserCoolTime = 0;
	int firingLaser = 0;
	bool islaser = false;
	Screen* screen;
public:
	Bullet(int pos, const char* face, Screen* screen, int bullet_count)
		: GameObject(pos, face, screen, bullet_count), isFiring(false), pos(pos), screen(screen)
	{

	}
	int moveLeft(int pos)
	{
		return (pos - 1);
	}
	int moveRight(int pos)
	{
		return (pos + 1);
	}
	void draw()
	{
		if (isFiring == false) return;
		GameObject::draw();
	}
	void drawWeapon2(int i)
	{
		if (isFiring == true)
			screen->draw(i, "=");
		else
			screen->draw(i, "\0");
	}
	bool coolTimeOn()
	{
		if (islaser) {
			laserCoolTime++;
			return true;
		}
		else
			return false;

	}
	bool getlaser()
	{
		return islaser;
	}
	void coolTimeOff()
	{
		if (laserCoolTime % 30 == 0) {
			laserCoolTime = 0;
			islaser = false;
		}
	}
	void changeWeapon()
	{
		if (weaponType == 0)
			weaponType = 1;
		else if (coolTimeOn() == false) {
			islaser = true;
			weaponType = 0;
		}
	}
	void fire(int player_pos)
	{
		if (weaponType == 0)
			changeLaser();
		else
			changeBullet();
		if (isFiring == true) {
			if (weaponType == 0)
				isFiring = false;
			else
				return;
		}
		else {
			isFiring = true;
			setPosition(player_pos);
		}
	}
	bool getFiring()
	{
		return isFiring;
	}
	void update(int enemy_pos, bool isLeft, const int screen_size, int player_pos)
	{
		if (isFiring == false) return;
		if (weaponType == 1) {
			pos = getPosition();
			if (isLeft) {
				if (pos > player_pos)
					pos = moveRight(pos);
				else
					pos = moveLeft(pos);
			}
			else {
				if (pos < player_pos)
					pos = moveLeft(pos);
				else
					pos = moveRight(pos);
			}
			if (enemy_pos == pos || pos == 0 || pos == screen_size) {
				isFiring = false;
			}
			setPosition(pos);
		}
		else {
			if (firingLaser == 10) {
				firingLaser = 0;
				isFiring = false;
				changeWeapon();
				return;
			}
			if (isLeft) {
				if (player_pos > enemy_pos) {
					for (int i = player_pos - 1; i > enemy_pos + 5; i--) {
						drawWeapon2(i);
					}
				}
				else {
					for (int i = player_pos - 1; i >= 0; i--) {
						drawWeapon2(i);
					}
				}
			}
			else {
				if (player_pos > enemy_pos) {
					for (int i = screen_size; i > player_pos + 4; i--) {
						drawWeapon2(i);
					}
				}
				else {
					for (int i = enemy_pos - 1; i > player_pos + 4; i--) {
						drawWeapon2(i);
					}
				}
			}
			firingLaser++;
		}
		if (islaser == true)
			coolTimeOn();
		coolTimeOff();

	}
};

int main()
{
	int GameTime = 0;
	int weaponType = 0;
	Screen screen{ 80 };
	Player player = { 30, "(>_>)", &screen, 10 };
	Enemy enemy{ 70, "(*--*)", &screen , 10 };
	Bullet bullet(-1, "+", &screen, 10);

	while (true)
	{
		screen.clear();

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.moveLeft();
				break;
			case 'd':
				player.moveRight();
				break;
			case ' ':
				bullet.fire(player.getPosition());
				break;
			case 'm':
				bullet.changeWeapon();
				break;
			}
		}
		bullet.draw();
		player.draw();
		enemy.draw();

		player.update(enemy.getPosition());
		enemy.update(player.getPosition(), GameTime, bullet.getPosition());
		bullet.update(enemy.getPosition(), player.getIsLeft(), screen.length(), player.getPosition());

		screen.render();
		GameTime++;
		Sleep(66);
	}

	return 0;
}

//1번 - 플레이어의 방향에 따라 시선이 바뀐다.
//2번 - 플레이어의 방향에 맞춰서 공격이 진행된다(현재 1발만 가능하여 화면상에서 사라지기 전까지 다른 총알을 생성하지 못하도록 설정)
//12번 - 적은 플레이어를 향해 지정된 시간에 따라 움직인다.(현재 생성된 위치를 기준으로 플레이어를 향해 이동)
//13번 - 각각의 오브젝트에 hp생성(bullet의 hp는 탄창 수를 의미), hp가 0이되면 화면에서 지워짐
//3번 - Enemy의 hp가 깎이는 부분에서 오류(1~5랜덤적 데미지), 레이저 구현 (데미지 미적용)
//7번 - m키를 사용하여 공격을 전환한다.
//5번 - 레이저건은 일정시간발사 후, 일정시간동안 일반공격에서 레이저건으로 변경이 불가능하다.