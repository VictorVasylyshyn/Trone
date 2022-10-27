#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#define RED RGB(255,0,0)
#define GRN RGB(0,255,0)
#define BLU RGB(0,0,255)
#define BLK RGB(0,0,0)
#define WHT RGB(255,255,255)
using namespace std;
class Game {
protected:
	bool m_startGame;
	const int width = 140;
	const int height = 70;
	enum locationInput {
		STOP = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN
	} dir;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	virtual void setup() = 0;
	virtual void draw() = 0;
	virtual void map(int i, int j, HANDLE hStdout) {}
	virtual locationInput input() = 0 {}
	virtual void logic() = 0 {}
	virtual void snakeCollision(std::vector<pair<int, int>>, std::vector<pair<int, int>>::iterator, std::vector<pair<int, int>>, std::vector<pair<int, int>>::iterator);
	virtual void setGame(bool n);
	COORD makeCoord(int x, int y);
	BOOL ShowConsoleCursor(BOOL bShow);
	
};
class Snake : public Game {
private:
	int x, y;

public:
	
	void setup() final;
	void map(int i, int j, HANDLE hStdout) final;
	void draw();
	void logic();
	locationInput input();
	static void SetPos(int x, int y);
	void drawSnake(int i, int j, int x, int y, HANDLE hStdout);
	void collision();
	//virtual void snakeCollision();
	virtual void setGame(bool n);
	bool getStartGame() const { return m_startGame; }
	int getX() const{ return x; }
	int getY() const{ return y; }

};
class SecondPlayer : public Game{
private:
	int x, y;
public:
	
	void setup();
	void logic();
	locationInput input();
	static void SetPos(int x, int y);
	void draw();
	void drawSnake(int i, int j, int x, int y, HANDLE hStdout);
	bool getStartGame() const { return m_startGame; }
	void collision();
	//virtual void snakeCollision(std::vector<pair<int, int>>, std::vector<pair<int, int>>::iterator, std::vector<pair<int, int>>, std::vector<pair<int, int>>::iterator);
	int getX() const { return x; }
	int getY() const { return y; }
};
class Menu {
public:
	int color = 5;
	int g = 0;
	void DrawMenu(HDC hDC, RECT pRECT, int iSEL, int iTITLE);
	void DrawSettings(HDC hDC, RECT pRECT, int iSEL, int iTITLE);
	void PlayerColor(HDC hDC, RECT pRECT, int iSEL, int iTITLE);
	void menu();
};
