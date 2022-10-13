#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
class Game {
protected:
	bool m_startGame;
	enum locationInput {
		STOP = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN
	} dir;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	const int width = 140;
	const int height = 70;
	virtual void setup();
	virtual void draw();
	virtual void map(int i, int j, HANDLE hStdout) {}
	virtual locationInput input() = 0 {}
	virtual void logic() = 0 {}
	virtual void setGame(bool n);
	virtual void collisionSnakes();
	COORD makeCoord(int x, int y);
	BOOL ShowConsoleCursor(BOOL bShow);
	
};
class Snake : public Game {
private:
	int x, y;

public:
	std::vector<pair<int,int>> a = { {width / 4, height / 2} };
	std::vector<pair<int, int>>::iterator it;
	void setup() final;
	void map(int i, int j, HANDLE hStdout) final;
	void draw();
	void logic();
	locationInput input();
	static void SetPos(int x, int y);
	void drawSnake(int i, int j, int x, int y, HANDLE hStdout);
	void collision();
	virtual void setGame(bool n);
	bool getStartGame() const { return m_startGame; }
	int getX() const{ return x; }
	int getY() const{ return y; }

};
class SecondPlayer : public Game{
private:
	int x, y;
public:
	std::vector<pair<int, int>> b = { {width / 6, height / 4} };
	std::vector<pair<int, int>>::iterator iter;
	void setup();
	void logic();
	locationInput input();
	static void SetPos(int x, int y);
	void draw();
	void drawSnake(int i, int j, int x, int y, HANDLE hStdout);
	bool getStartGame() const { return m_startGame; }
	void collision();
	int getX() const { return x; }
	int getY() const { return y; }
};
