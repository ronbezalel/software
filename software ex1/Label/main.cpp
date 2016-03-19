// testLable.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <stdio.h>
#include "Label.h"


int main() {
	CONSOLE_CURSOR_INFO cci = { 100, false };
	Label l = Label(25, 5, "this is the label", cci);

	DWORD dw = FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	l.SetColor(dw);
	l.Print();

	return 0;
}