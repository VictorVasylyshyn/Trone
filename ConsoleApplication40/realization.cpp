#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include "Header.h"
using namespace std;
namespace coord {
	std::vector<pair<int, int>> a = { {140 / 4, 70 / 2} };
	std::vector<pair<int, int>>::iterator it;
	std::vector<pair<int, int>> b = { {140 / 6, 70 / 4} };
	std::vector<pair<int, int>>::iterator iter;
}

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

void Snake::drawSnake(int i, int j, int x, int y, HANDLE hStdout) {

	char w[3] = { 201,210 , 187 };
	char s[3] = { 198,206 ,181 };
	char n[3] = { 200,208 ,188 };
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

	char w[3] = { 201,210 , 187 };
	char s[3] = { 198,206 ,181 };
	char n[3] = { 200,208 ,188 };
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
	for (coord::it = coord::a.begin(); coord::it != coord::a.end()-1; ++coord::it)
	{
		if (x == (coord::it->first) && y == (coord::it->second))
		{
			setGame(true);
			cout << "PLAYER TWO WIN!";
		}
	}
}
void SecondPlayer::collision() {
	for (coord::iter = coord::b.begin(); coord::iter != coord::b.end() - 1; ++coord::iter)
	{
		if (x == (coord::iter->first) && y == (coord::iter->second))
		{
			setGame(true);
			cout << "PLAYER ONE WIN!";
		}
	}
}

void Snake::logic(){
	switch (dir)
	{
	case Game::LEFT:
		y--;
		coord::a.push_back(pair<int,int>(x,y));
		break;
	case Game::RIGHT:
		y++;
		coord::a.push_back(pair<int, int>(x, y));
		break;
	case Game::UP:
		x--;
		coord::a.push_back(pair<int, int>(x, y));
		break;
	case Game::DOWN:
		x++;
		coord::a.push_back(pair<int, int>(x, y));
		break;
	
	}
	if (dir!=STOP)
	{
		collision();
		snakeCollision(coord::a, coord::it, coord::b, coord::iter);
		if (y<0 || y > width - 2 || x < 0 || x > height - 2) {
			setGame(true);
			cout << "PLAYER TWO WIN!";
		}
		
	}
	
	
}

void SecondPlayer::logic() {
	switch (dir)
	{
	case Game::LEFT:
		y--;
		coord::b.push_back(pair<int, int>(x, y));
		break;
	case Game::RIGHT:
		y++;
		coord::b.push_back(pair<int, int>(x, y));
		break;
	case Game::UP:
		x--;
		coord::b.push_back(pair<int, int>(x, y));
		break;
	case Game::DOWN:
		x++;
		coord::b.push_back(pair<int, int>(x, y));
		break;

	}
	if (dir != STOP)
	{
		collision();
		snakeCollision(coord::a, coord::it, coord::b, coord::iter);
		if (y<0 || y > width - 2 || x < 0 || x > height - 2) {
			setGame(true);
			cout << "PLAYER ONE WIN!";
		}
	}

}
void Game::snakeCollision(std::vector<pair<int, int>> f_a, std::vector<pair<int, int>>::iterator it_a, std::vector<pair<int, int>> f_b, std::vector<pair<int, int>>::iterator it_b) {

	for (it_a = f_a.begin(); it_a != f_a.end(); it_a++) {
		for (it_b = f_b.begin(); it_b != f_b.end(); it_b++) {
			if (it_a->first == it_b->first && it_a->second == it_b->second)
			{
				setGame(true);
			}
		}

	}
}

void Menu::DrawMenu(HDC hDC, RECT pRECT, int iSEL, int iTITLE)
{
	//Толщина заголовка консоли
	char sMENU[] = "***MENU***";
	const char* sITEM[] =
	{
		"S T A R T",
		"S E T T I N G S",
		"E X I T"
	};
	char sARROW[] = " -> ";
	BitBlt(hDC,
		4, iTITLE,
		pRECT.right - pRECT.left,
		pRECT.bottom - pRECT.top,
		hDC,
		4, iTITLE,
		BLACKNESS);
	SetTextColor(hDC, BLU);
	TextOutA(hDC, 70, iTITLE, sMENU, strlen(sMENU));
	for (int iITEM = 0; iITEM < 3; iITEM++)
	{
		SetTextColor(hDC, GRN);
		if (iITEM == iSEL)
		{
			SetTextColor(hDC, RED);
			TextOutA(hDC, 55, iTITLE + (1 + iITEM) * 12, sARROW, strlen(sARROW));
			TextOutA(hDC, 70, iTITLE + (1 + iITEM) * 12, sITEM[iITEM], strlen(sITEM[iITEM]));
		}
		else
			TextOutA(hDC, 60, iTITLE + (1 + iITEM) * 12, sITEM[iITEM], strlen(sITEM[iITEM]));
	}
}
void Menu::DrawSettings(HDC hDC, RECT pRECT, int iSEL, int iTITLE)
{
	//Толщина заголовка консоли
	char sMENU[] = "***CHOOSE COLOR***";
	const char* sITEM[] =
	{

		"YELLOW",
		"RED",
		"GREEN",
		"BLUE",
		"<-BACK"
	};
	char sARROW[] = " -> ";
	BitBlt(hDC,
		4, iTITLE,
		pRECT.right - pRECT.left,
		pRECT.bottom - pRECT.top,
		hDC,
		4, iTITLE,
		BLACKNESS);
	SetTextColor(hDC, BLU);
	TextOutA(hDC, 70, iTITLE, sMENU, strlen(sMENU));
	for (int iITEM = 0; iITEM < 5; iITEM++)
	{
		SetTextColor(hDC, GRN);
		if (iITEM == iSEL)
		{

			SetTextColor(hDC, RED);
			TextOutA(hDC, 55, iTITLE + (1 + iITEM) * 12, sARROW, strlen(sARROW));
			TextOutA(hDC, 70, iTITLE + (1 + iITEM) * 12, sITEM[iITEM], strlen(sITEM[iITEM]));
		}
		else
			TextOutA(hDC, 70, iTITLE + (1 + iITEM) * 12, sITEM[iITEM], strlen(sITEM[iITEM]));
	}
}
void Menu::PlayerColor(HDC hDC, RECT pRECT, int iSEL, int iTITLE)
{
	//Толщина заголовка консоли
	char sMENU[] = "***CHOOSE COLOR***";
	const char* sITEM[] =
	{

		"PLAYER 1",
		"PLAYER 2",
		"<-BACK"
	};
	char sARROW[] = " -> ";
	BitBlt(hDC,
		4, iTITLE,
		pRECT.right - pRECT.left,
		pRECT.bottom - pRECT.top,
		hDC,
		4, iTITLE,
		BLACKNESS);
	SetTextColor(hDC, BLU);
	TextOutA(hDC, 70, iTITLE, sMENU, strlen(sMENU));
	for (int iITEM = 0; iITEM < 2; iITEM++)
	{
		SetTextColor(hDC, GRN);
		if (iITEM == iSEL)
		{

			SetTextColor(hDC, RED);
			TextOutA(hDC, 55, iTITLE + (1 + iITEM) * 12, sARROW, strlen(sARROW));
			TextOutA(hDC, 70, iTITLE + (1 + iITEM) * 12, sITEM[iITEM], strlen(sITEM[iITEM]));
		}
		else
			TextOutA(hDC, 70, iTITLE + (1 + iITEM) * 12, sITEM[iITEM], strlen(sITEM[iITEM]));
	}
}

void Menu::menu() {
	int  iSEL = 0;
	int  nYRes = GetSystemMetrics(SM_CYMENUSIZE) * 2;
	HDC  hDC;
	HDC shDC;
	RECT pRECT;
	RECT spRECT;
	HWND hWnd = GetForegroundWindow();
	HWND ShWnd = GetForegroundWindow();
	if (hWnd)
	{

		if (hDC = GetWindowDC(hWnd))
		{
			SetBkMode(hDC, TRANSPARENT);
			GetClientRect(hWnd, &pRECT);
		link1:
			while (!g)
			{
				DrawMenu(hDC, pRECT, iSEL, nYRes);
				RedrawWindow(hWnd, NULL, NULL,
					RDW_ERASE | RDW_VALIDATE | RDW_UPDATENOW);

				switch (toupper(_getch()))
				{
				case 'W':
					PlaySound(L"menu.wav", NULL, SND_ASYNC);
					if ((iSEL = iSEL - 1) < 0)
						iSEL = 2;
					break;
				case 'S':
					PlaySound(L"menu.wav", NULL, SND_ASYNC);
					if (2 < (iSEL = iSEL + 1))
						iSEL = 0;
					break;
				case 13:
					if (iSEL == 0) {
						g = 1;
					}
					if (iSEL == 2) {
						exit(0);
					}
					if (iSEL == 1) {
						if (ShWnd)
						{
							iSEL = 0;
							if (shDC = GetWindowDC(hWnd))
							{
								SetBkMode(shDC, TRANSPARENT);
								GetClientRect(ShWnd, &spRECT);
								while (true)
								{
									
									PlayerColor(shDC, spRECT, iSEL, nYRes);
									RedrawWindow(hWnd, NULL, NULL,
										RDW_ERASE | RDW_VALIDATE | RDW_UPDATENOW);
									switch (toupper(_getch()))
									{
									case 'W':
										if ((iSEL = iSEL - 1) < 0)
											iSEL = 1;
										break;
									case 'S':
										if (4 < (iSEL = iSEL + 1))
											iSEL = 0;
										break;
									case 13:
										if (iSEL == 1) {
											if (ShWnd)
											{
												iSEL = 0;
												if (shDC = GetWindowDC(hWnd))
												{
													SetBkMode(shDC, TRANSPARENT);
													GetClientRect(ShWnd, &spRECT);
													while (true)
													{
														DrawSettings(shDC, spRECT, iSEL, nYRes);
														RedrawWindow(hWnd, NULL, NULL,
															RDW_ERASE | RDW_VALIDATE | RDW_UPDATENOW);
														switch (toupper(_getch()))
														{
														case 'W':
															if ((iSEL = iSEL - 1) < 0)
																iSEL = 1;
															break;
														case 'S':
															if (4 < (iSEL = iSEL + 1))
																iSEL = 0;
															break;
														case 13:
															if (iSEL == 4) {
																goto link1;
															}
															if (iSEL == 0) {
																color = 14;

																goto link1;
															}
															if (iSEL == 1) {
																color = 4;

																goto link1;
															}
															if (iSEL == 2) {
																color = 2;

																goto link1;
															}
															if (iSEL == 3) {
																color = 1;

																goto link1;
															}
															break;

														};
													}
												}
											}
										}
										if (iSEL == 0) {
											if (ShWnd)
											{
												iSEL = 0;
												if (shDC = GetWindowDC(hWnd))
												{
													SetBkMode(shDC, TRANSPARENT);
													GetClientRect(ShWnd, &spRECT);
													while (true)
													{
														DrawSettings(shDC, spRECT, iSEL, nYRes);
														RedrawWindow(hWnd, NULL, NULL,
															RDW_ERASE | RDW_VALIDATE | RDW_UPDATENOW);
														switch (toupper(_getch()))
														{
														case 'W':
															if ((iSEL = iSEL - 1) < 0)
																iSEL = 1;
															break;
														case 'S':
															if (4 < (iSEL = iSEL + 1))
																iSEL = 0;
															break;
														case 13:
															if (iSEL == 4) {
																goto link1;
															}
															if (iSEL == 0) {
																color = 14;

																goto link1;
															}
															if (iSEL == 1) {
																color = 4;

																goto link1;
															}
															if (iSEL == 2) {
																color = 2;

																goto link1;
															}
															if (iSEL == 3) {
																color = 1;

																goto link1;
															}
															break;

														};
													}
												}
											}
										}
										
										break;

									};
								}
							}
						}
					}
					break;

				};
			}
		}
	}
}