#include "screen.h"

#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

screen::screen(int width, int height)
{
	initscr();
	this->width = width;
	this->height = height;
	this->grid = new char*[width];
	for(int i = 0; i < width; i++)
	{
		this->grid[i] = new char[height];
	}
	clear(' ');
	srand((unsigned) time(0));
}

screen::screen()
{
	initscr();
	getmaxyx(stdscr, height, width);
	this->grid = new char*[width];
	for(int i = 0; i < width; i++)
	{
		this->grid[i] = new char[height];
	}
	clear(' ');
	srand((unsigned) time(0));
}

screen::~screen()
{
	for(int i = 0; i < width; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
	endwin();
}

int screen::init()
{
	doColor = has_colors();
	if(doColor)
	{
		start_color();
		init_pair(NORMAL_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(GREEN_COLOR, COLOR_GREEN, COLOR_BLACK);
	}
	int echoErr = noecho();
	int cbreakErr = cbreak();
	int nodelayErr = nodelay(stdscr, 1);
	if(echoErr == ERR)
	{
		std::cout << "fatal: Could not set noecho" << std::endl;
		return echoErr;
	}
	if(cbreakErr == ERR)
	{
		std::cout << "fatal: Could not set cbreak" << std::endl;
		return cbreakErr;
	}
	if(nodelayErr == ERR)
	{
		std::cout << "fatal: Could not set nodelay" << std::endl;
		return nodelayErr;
	}
	return 1;
}

int screen::getTypedCharacter()
{
	return getch();
}

void screen::setCharacterAt(int x, int y, char character)
{
	*(*(grid + x) + y) = character;
	move(y, x);
	curs_set(0);
	printw("%c", character);
}

void screen::setCharacterAt(int x, int y, char character, int color)
{
	attron(COLOR_PAIR(color));
	setCharacterAt(x, y, character);
	attroff(COLOR_PAIR(color));
}

char screen::getCharacterAt(int x, int y)
{
	return *(*(grid + x) + y);
}

void screen::draw()
{
	refresh();
}

void screen::printText(char* text, int length, int x, int y)
{
	int printX = x;
	if (length < 0)
		length = strlen(text);
	for(int dx = x; dx < x + length; dx++)
	{
		setCharacterAt(printX++, y, text[dx - x]);  //this is where we inc printX
		if (text[dx - x] == '\n')
		{
			y++;
			printX = x;
		}
	}
}

void screen::printText(char* text, int length, int x, int y, int color)
{
	attron(COLOR_PAIR(color));
	printText(text, length, x, y);
	attroff(COLOR_PAIR(color));
}

void screen::printTextCentered(char* text, int length)
{
	int y = height / 2;
	int x = width / 2 - (length / 2);
	printText(text, length, x, y);
}

void screen::printTextCenteredGreen(char* text, int length)
{
	attron(COLOR_PAIR(GREEN_COLOR));
	printTextCentered(text, length);
	attroff(COLOR_PAIR(GREEN_COLOR));
}

void screen::clear(char space)
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			setCharacterAt(x, y, space);
		}
	}
}

void screen::randomize()
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			char randChar = (rand() % 127) + 32;
			setCharacterAt(x, y, randChar, NORMAL_COLOR);
		}
	}
}
