
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

	/* Label Main */
	Label l = Label(15, 0, "yossi is mega gay, learn how to build fuckig automat!!", true);
	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	l.SetColor(dw);
	l.Print();
	////////////////////////////////////////////////////////////////////////////////////////


	/* to test one of the controllers comment the "Label main" and un-commet the requested controller */
	string list[5] = {
		"yossi gay 1",
		"yossi gay 2",
		"yossi gay 3",
		"yossi gay 4",
		"yossi gay 5"
	};
	///////////////////////////////////////////////////////////////////////////////////////
	/*un-commet the requested controller*/
	//CheckList controller = CheckList(list, 5, 10, 10, dw);
	//RadioList controller = RadioList(list, 5, 10, 10, dw);
	//TextBox controller = TextBox(10, 15, 14);
	ComboBox controller = ComboBox(list, 5, 5, 5, dw);
	controller.Print();
	////////////////////////////////////////////////////////////////////////////////////
	
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
			controller.HandleInput(irInBuf[i]);
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