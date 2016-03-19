// testLable.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <stdio.h>


int main() {


	COORD c = { 25, 5 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);

	//set cursor size and visibility example
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);

	//set foreground color
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);


	////BACKGROUND/////////////////////////////////////////////////////////////
	//CONSOLE_SCREEN_BUFFER_INFO cbi;

	//GetConsoleScreenBufferInfo(h, &cbi);

	//DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE | BACKGROUND_GREEN;
	//SetConsoleTextAttribute(h, wAttr2);
	////////////////////////////////////////////////////////////////////////////
	int x = 90;

	printf("hello shenitzko and pasta ? \n\n\n\n\n\n");








	return 0;
}