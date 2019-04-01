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
		*(randomText + i - 1) = new char[len];
		strcpy(*(randomText + i - 1), argv[i]);
	}
	
	std::cout << length << std::endl;

	//Create a buffer for the text we are writing in the center
	char** centerDisplay = new char*[argc - 1];
	for(int i = 0; i < argc - 1; i++)
	{
		int len = strlen(*(randomText + i));
		*(centerDisplay + i) = new char[len];
		for(int j = 0; j < len; j++)
		{
			*(*(centerDisplay + i) + j) = (rand() % 127) + 32; //Pick random characters
		}
	}

	//Randomize the order that we reveal the characters
	int** randomIndexOrder = new int*[length];
	for(int i = 0; i < length; i ++)
	{
		int len = strlen(*(randomText + i)); // Need to convert remaining code to use 2d arrays for multiple lines
	}
	for(int i = 0; i < length; i++)
	{
		*(randomIndexOrder + i) = i;
	}
	//Shuffle
	for(int i = length - 1; i > 0; i--)
	{
		int j = rand() % i;
		int temp = *(randomIndexOrder + i);
		*(randomIndexOrder + i) = *(randomIndexOrder + j);
		*(randomIndexOrder + j) = temp;
	}

	//Initialize screen
	screen window;
	int err = window.init();
	if(err <= 0)
		return err;

	//Main loop
	bool run = true;
	int lettersShown = 0;
	while(run)
	{
		//Handle input
		char ch = window.getTypedCharacter();
		if(ch == 'q')
			run = false;
		//Randomize message
		if(rand() < (RAND_MAX / (FPS / 3)) && lettersShown < length)
		{
			lettersShown++;
		}
		for(int i = 0; i < lettersShown; i++)
		{
			int j = *(randomIndexOrder + i);
			*(centerDisplay + j) = *(randomText + j); 
		}
		//Draw text
		window.randomize();
		window.printTextCenteredGreen(centerDisplay, length);
		window.draw();
		usleep(FRAMETIME);
	}

	delete[] centerDisplay;
	delete[] randomIndexOrder;
	for(int i = 0; i < argc - 1; i++)
	{
		delete[] *(randomText + i);
	}
	delete[] randomText;

	return 0;
}
