#include "screen.h"
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <unistd.h>

#define FPS (60)
#define FRAMETIME (1000000 / FPS)

int main(int argc, char* argv[])
{
	//Handle input
	if(argc <= 1)
	{
		std::cout << "Too little arguments" << std::endl;
		return 1;
	}
	if(argc > 2)
	{
		std::cout << "Too many arguments" << std::endl;
		return 1;
	}
	char* randomText = argv[1];
	int length = strlen(randomText);
	
	std::cout << length << std::endl;

	//Create a buffer for the text we are writing in the center
	char* centerDisplay = new char[length];
	for(int i = 0; i < length; i++)
	{
		*(centerDisplay + i) = (char) 177; //Initialize to weird dotted block thingies
	}

	//Randomize the order that we reveal the characters
	int* randomIndexOrder = new int[length];
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
		if(rand() < (RAND_MAX / FPS) && lettersShown < length + 1)
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

	return 0;
}
