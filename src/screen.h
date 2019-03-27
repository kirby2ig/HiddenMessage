#ifndef SCREEN_H
#define SCREEN_H

#include "string.h"

class screen
{
    public:
	screen();
        screen(int width, int height);
        ~screen();
	int init();
        void setCharacterAt(int x, int y, char character);
	void setCharacterAt(int x, int y, char character, int color);
        char getCharacterAt(int x, int y);
        void draw();
        void printText(char* text, int length, int x, int y);
	void printTextCentered(char* text, int length);
	void printTextCenteredGreen(char* text, int length);
        void clear(char space);
        void print(char* string, int length);
	int getTypedCharacter();
	void randomize();
    private:
        char** grid;
        int width;
        int height;
	bool doColor;
}
;

#endif
