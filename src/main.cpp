#include "screen.h"
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <unistd.h>

#define FPS (30)
#define FRAMETIME (1000000 / FPS)

int main(int argc, char* argv[])
{
	//Handle input
	if(argc <= 1)
	{
		std::cout << "Too little arguments" << std::endl;
		return 1;
	}

	char** randomText = new char*[argc - 1];
	for(int i = 1; i < argc; i++)
	{
		char* nextLine = argv[i];
		int len = strlen(nextLine);
		*(randomText + i - 1) = new char[len + 1];
		strcpy(*(randomText + i - 1), argv[i]);
	}
	
	//Create a buffer for the text we are writing in the center
	char** centerDisplay = new char*[argc - 1];
	for(int i = 0; i < argc - 1; i++)
	{
		int len = strlen(*(randomText + i));
		*(centerDisplay + i) = new char[len+ 1];
		for(int j = 0; j < len; j++)
		{
			*(*(centerDisplay + i) + j) = (rand() % 127) + 32; //Pick random characters
		}
	}

	//Randomize the order that we reveal the characters
	int** randomIndexOrder = new int*[argc - 1];
	for(int i = 0; i < argc - 1; i ++)
	{
		int len = strlen(*(randomText + i));
		*(randomIndexOrder + i) = new int[len];
		for(int j = 0; j < len; j++)
		{
			*(*(randomIndexOrder + i) + j) = j;
		}
		//Shuffle
		for(int j = len - 1; j > 0; j--)
		{
			int k = rand() % j;
			int temp = *(*(randomIndexOrder + i) + j);
			*(*(randomIndexOrder + i) + j) = *(*(randomIndexOrder + i) + k);
			*(*(randomIndexOrder + i) + k) = temp;
		}
	}

	//Initialize screen
	screen window;
	int err = window.init();
	if(err <= 0)
		return err;

	//Main loop
	bool run = true;
	int* lettersShown = new int[argc - 1];
	for(int i = 0; i < argc - 1; i++)
	{
		*(lettersShown + i) = 0;
	}
	while(run)
	{
		//Handle input
		char ch = window.getTypedCharacter();
		if(ch == 'q')
			run = false;

		//Randomize message
		if(rand() < (RAND_MAX / (FPS / 3)))
		{
			for(int i = 0; i < argc - 1; i++)
			{
				if(*(lettersShown + i) < strlen(*(randomText + i)))
					(*(lettersShown + i))++;
			}
		}
		for(int i = 0; i < argc - 1; i++)
		{
			for(int j = 0; j < *(lettersShown + i); j++)
			{
				int k = *(*(randomIndexOrder + i) + j);
				*(*(centerDisplay + i) + k) = *(*(randomText + i) + k);
			}
		}
		//Draw text
		window.randomize();
		for(int i = 0; i < argc - 1; i++)
		{
			// void printText(char* text, int length, int x, int y, int color);
			int len = strlen(*(centerDisplay + i));
			int x = window.getWidth() / 2 - len / 2;
			int y = window.getHeight() / 2 - argc - 1 + i;
			window.printText(*(centerDisplay + i), len, x, y, GREEN_COLOR);
		}
		window.draw();
		usleep(FRAMETIME);
	}

	for(int i = 0; i < argc - 1; i++)
	{
		delete[] *(centerDisplay + i);
	}
	delete[] centerDisplay;

	for(int i = 0; i < argc - 1; i++)
	{
		delete[] *(randomIndexOrder + i);
	}
	delete[] randomIndexOrder;
	
	for(int i = 0; i < argc - 1; i++)
	{
		delete[] *(randomText + i);
	}
	delete[] randomText;

	delete[] lettersShown;

	return 0;
}
