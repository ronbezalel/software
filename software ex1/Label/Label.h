#ifndef _LABEL_H_
#define _LABEL_H_

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
class Label
{
private:
	COORD cord = { 0,0 };
	HANDLE handle;
	DWORD dw;
	CONSOLE_CURSOR_INFO cci;

	string labelText;


public:
	Label(short width, short highet, string text, CONSOLE_CURSOR_INFO _cci);
	void SetColor(DWORD color);
	void Print();
	~Label();
};


#endif // !_LABEL_H_


