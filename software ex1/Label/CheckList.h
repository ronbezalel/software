#ifndef _CHECKLIST_H_
#define _CHECKLIST_H_

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Label.h"
#include <vector>

class CheckList
{
protected:
	vector<Label> list;
	bool* chosen;
	short currentRow = 0;
	short currentPosition = 0;
	int rowMaxLength = 0;
	HANDLE handle;
	COORD startPoint;
	
	//private func:
	void MoveUp();
	void MoveDown();
	virtual void Mark();
	void MousePressed(MOUSE_EVENT_RECORD mer);
	void MouseMoved(MOUSE_EVENT_RECORD mer);
	int CheckPosition(MOUSE_EVENT_RECORD mer);

public:
	CheckList(string* textList, int listSize, short width, short hieght, DWORD color);
	void Print();
	bool* GetChosenRows();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void HandleInput(INPUT_RECORD iRecord);
	string GetChosen();
	~CheckList();
};

#endif

