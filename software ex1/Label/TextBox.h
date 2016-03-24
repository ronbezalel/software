#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include <string>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;
class TextBox
{
private:
	vector<char> text;
	int boxSize;
	int curserPosition;
	int textIndex = 0;
	HANDLE handle;
	COORD startPoint;
	bool focus = false;

	void MoveRight();
	void MoveLeft();
	void Delete();
	void AddCharecter(char c);
	int CheckPosition(MOUSE_EVENT_RECORD mer);
	void MousePressed(MOUSE_EVENT_RECORD mer);

public:
	TextBox(int boxLength, short width, short hieght);
	void Print();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void HandleInput(INPUT_RECORD iRecord);
	string GetText();
	~TextBox();
};


#endif // _TEXTBOX_H_



