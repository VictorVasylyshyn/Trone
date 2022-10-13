
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include "Header.h"
using namespace std;
void Game::setGame(bool n) {
	m_startGame = n;
}
void Snake::setGame(bool n) {
	m_startGame = n;
}
void Snake::SetPos(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void SecondPlayer::SetPos(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
COORD Game::makeCoord(int x, int y) {
	COORD coord = { (short)x,(short)y };
	return coord;
}
BOOL Game::ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hiStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hiStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hiStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hiStdOut, &cci))
		return FALSE;
	return TRUE;
}


void Snake::setup() {
	dir = STOP;
	x = width / 4;
	y = height / 2;
	ShowConsoleCursor(false);
}
void SecondPlayer::setup() {
	dir = STOP;
	x = width / 6;
	y = height / 4;
	ShowConsoleCursor(false);
}
void Snake::map(int i, int j, HANDLE hStdout) {
	if (j == (height - 1) || j == 0) {
		SetPos(i, j);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x55);
		cout << char(196);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	}

	else if (i == (width - 1) || i == 0) {
		SetPos(i, j);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x55);
		cout << char(179);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	}

}
char w[3] = { 201,210 , 187 };
char s[3] = { 198,206 ,181 };
char n[3] = { 200,208 ,188 };
void Snake::drawSnake(int i, int j, int x, int y, HANDLE hStdout) {

	if (j == x - 1 && i == y) {
		SetPos(i, j);


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x55);
		for (int k = 0; k < 3; k++) {
			cout << w[k];
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);

	}
	else if (j == x && i == y) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x55);
		SetPos(i, j);
		for (int k = 0; k < 3; k++) {
			cout << w[k];

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);

	}
	

}
void SecondPlayer::drawSnake(int i, int j, int x, int y, HANDLE hStdout) {

	if (j == x - 1 && i == y) {
		SetPos(i, j);


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x55);
		for (int k = 0; k < 3; k++) {
			cout << w[k];
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);

	}
	else if (j == x && i == y) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x55);
		SetPos(i, j);
		for (int k = 0; k < 3; k++) {
			cout << s[k];

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);

	}

}
void Snake::draw() {
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			map(i, j, hStdout);
			drawSnake(i, j, x, y, hStdout);
		}
	}
	
}
void SecondPlayer::draw() {
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			drawSnake(i, j, x, y, hStdout);
		}
	}

}
Game::locationInput Snake::input() {
	if (_kbhit()) { //keylog

		switch (_getch()) // ждёт нажатия на клаву без Enter после этого
		{
		case 'w': //вверх
			dir = UP;
			return dir;
			break;
		case 's': //вниз
			dir = DOWN;
			return dir;
			break;
		case 'a': //влево 
			dir = LEFT;
			return dir;
			break;
		case 'd': //вправо
			dir = RIGHT;
			return dir;
			break;
		case 27:
			m_startGame = true;
			break;
		}

	}
}
Game::locationInput SecondPlayer::input() {
	if (_kbhit()) { //keylog

		switch (_getch()) // ждёт нажатия на клаву без Enter после этого
		{
		case 72: //вверх
			dir = UP;
			return dir;
			break;
		case 80: //вниз
			dir = DOWN;
			return dir;
			break;
		case 75: //влево 
			dir = LEFT;
			return dir;
			break;
		case 77: //вправо
			dir = RIGHT;
			return dir;
			break;
		case 27:
			setGame(true);
			break;
		}

	}
}
void Snake::collision() {
	for (it = a.begin(); it != a.end()-1; it++)
	{
		if (x == (it->first) && y == (it->second))
		{
			setGame(true);
		}
	}
}
void SecondPlayer::collision() {
	for (iter = b.begin(); iter != b.end() - 1; iter++)
	{
		if (x == (iter->first) && y == (iter->second))
		{
			setGame(true);
		}
	}
}
void Snake::logic(){
	switch (dir)
	{
	case Game::LEFT:
		y-=2;
		a.push_back(pair<int,int>(x,y));
		break;
	case Game::RIGHT:
		y+=2;
		a.push_back(pair<int, int>(x, y));
		break;
	case Game::UP:
		x-=2;
		a.push_back(pair<int, int>(x, y));
		break;
	case Game::DOWN:
		x+=2;
		a.push_back(pair<int, int>(x, y));
		break;
	
	}
	collision();
	if (y<0 || y > width-2 || x < 0 || x > height-2) {
		setGame(true);
	}
	
}

void SecondPlayer::logic() {
	switch (dir)
	{
	case Game::LEFT:
		y -= 2;
		b.push_back(pair<int, int>(x, y));
		break;
	case Game::RIGHT:
		y += 2;
		b.push_back(pair<int, int>(x, y));
		break;
	case Game::UP:
		x -= 2;
		b.push_back(pair<int, int>(x, y));
		break;
	case Game::DOWN:
		x += 2;
		b.push_back(pair<int, int>(x, y));
		break;

	}
	collision();
	if (y < 0 || y > width - 2 || x < 0 || x > height - 2) {
		setGame(true);
	}

}