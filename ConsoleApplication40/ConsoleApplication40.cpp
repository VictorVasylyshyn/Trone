// ConsoleApplication40.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include "Header.h"
using namespace std;

int main()
{
	
	Snake snake;
	SecondPlayer plr;
	snake.setup();
	plr.setup();
	while (!(plr.getStartGame() || snake.getStartGame()))
	{
		system("mode con cols=226 lines=77");
		snake.draw();
		plr.draw();
		snake.input();
		plr.input();
		snake.logic();
		plr.logic();
	}
	
}
