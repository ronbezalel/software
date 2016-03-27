
#include <Windows.h>
#include <stdio.h>
#include "Label.h"
#include "CheckList.h"
#include "RadioList.h"
#include "TextBox.h"
#include "ComboBox.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR lpszMessage);

int main() {
	//Label Main
	
	//Label l = Label(15, 0, "this is the label", true);
	//Label l2 = Label(15,5, "b;lalalalala", true);
	//Label l3 = Label(15,7, "b;lalalalala", true);
	//DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	//DWORD dwcopy = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	//DWORD dw1 = (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) | dwcopy;
	//DWORD dw2 = (~BACKGROUND_RED | ~BACKGROUND_GREEN | ~BACKGROUND_BLUE) & dw;
	//l.SetColor(dw);
	//l2.SetColor(dw1);
	//l3.SetColor(dw2);
	//l.Print();
	//l2.Print();
	//l3.Print();
	
	/*
	//CheckBox Main
	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	string list[5] = {
		"yossi gay 1",
		"yossi gay 2",
		"yossi gay 3",
		"yossi gay 4",
		"yossi gay 5"
	};
	CheckList box = CheckList(list, 5, 10, 10, dw);
	int x = 90;
	box.Print();
	*/
	//radio list main
	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	string list[5] = {
		"yossi gay 1",
		"yossi gay 2",
		"yossi gay 3",
		"yossi gay jfjskfjksfj 4",
		"yossi gay 5"
	};

	ComboBox box = ComboBox(list, 5, 5, 5, dw);
	int x = 90;
	box.PrintComboBox();

	//textBox main
	//TextBox t = TextBox(10,15,14);
	//t.Print();
	//cout << endl;
	//t.SetText("eyal");

	
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 
	while (true)
	{
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++) {
			//Send the input record to the textbox handler
			box.HandleInput(irInBuf[i]);
		}
	}
	

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	return 0;
}

void ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}