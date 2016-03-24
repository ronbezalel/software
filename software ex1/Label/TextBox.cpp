#include "TextBox.h"



TextBox::TextBox(int boxLength, short width, short hieght) {
	boxSize = boxLength;
	startPoint = { width , hieght };
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	text = vector<char>(boxLength);
	CONSOLE_CURSOR_INFO newCci = { 100, true };
	SetConsoleCursorInfo(handle, &newCci);
}

void TextBox::Print() {
	DWORD dw = FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY;
	for (short i = startPoint.X; i < startPoint.X + boxSize+2; i++) {
		COORD tmpCoord = {i,startPoint.Y};
		SetConsoleCursorPosition(handle, tmpCoord);
		SetConsoleTextAttribute(handle, dw);
		if (i == startPoint.X) {
			tmpCoord.Y = tmpCoord.Y;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xDA';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xB3';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xC0';
			continue;
		}
		if (i == startPoint.X + boxSize + 1) {
			tmpCoord.Y = tmpCoord.Y;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xBF';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xB3';
			tmpCoord.Y = tmpCoord.Y + 1;
			SetConsoleCursorPosition(handle, tmpCoord);
			cout << '\xD9';
			continue;
		}
		cout << '\xC4';
		tmpCoord.Y = tmpCoord.Y + 2;
		SetConsoleCursorPosition(handle, tmpCoord);
		cout << '\xC4';
	}
	curserPosition = startPoint.X;
	COORD endPrint = { curserPosition, startPoint.Y};
	SetConsoleCursorPosition(handle, endPrint);
}

TextBox::~TextBox()
{
}

void TextBox::HandleInput(INPUT_RECORD iRecord) {
	//if (!isClicked) return;
	switch (iRecord.EventType)
	{
	case KEY_EVENT: // keyboard input 
		KeyEventProc(iRecord.Event.KeyEvent);
		break;

	case MOUSE_EVENT: // mouse input 
		MouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		//errorInput();
		break;
	}
}

void TextBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags) {

	case 0:
		//Right button press
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			MousePressed(mer);
		}
		break;
	}
}

void TextBox::MousePressed(MOUSE_EVENT_RECORD mer) {
	int res = CheckPosition(mer);
	if (res != -1) {
		curserPosition = res;
		textIndex = res - startPoint.X-1;
		COORD reset = { res , startPoint.Y + 1 };
		SetConsoleCursorPosition(handle, reset);
		focus = true;
	}
}

int TextBox::CheckPosition(MOUSE_EVENT_RECORD mer) {
	int YAxis = mer.dwMousePosition.Y;
	int XAxis = mer.dwMousePosition.X;
	if (XAxis <= startPoint.X + boxSize && XAxis >= startPoint.X + 1 &&
		YAxis == startPoint.Y+1) {
		return XAxis;
	}
	return -1;
}

void TextBox::KeyEventProc(KEY_EVENT_RECORD ker) {
	if (ker.bKeyDown) {
		switch (ker.wVirtualKeyCode)
		{
		case VK_LEFT:
		case VK_NUMPAD4:
			MoveLeft();
			break;
		case VK_NUMPAD6:
		case VK_RIGHT:
			MoveRight();
			break;
		case VK_BACK:
			Delete();
			break;
		default:
			AddCharecter(ker.uChar.AsciiChar);
			break;
		}
	}
}
void TextBox::MoveLeft() {
	if (curserPosition > startPoint.X + 1) {
		curserPosition--;
		COORD left = { curserPosition , startPoint.Y + 1 };
		SetConsoleCursorPosition(handle, left);
		if (focus) {
			textIndex--;
		}
		else focus = true;
	}
}

void TextBox::MoveRight() {
	if (curserPosition < startPoint.X + boxSize + 1) {
		curserPosition++;
		COORD right = { curserPosition , startPoint.Y + 1 };
		SetConsoleCursorPosition(handle, right);
		if (focus) {
			textIndex++;
		}
		else focus = true;
	}
}

void TextBox::Delete() {
	if (focus) {
		int offset = 1;
		for (int i = textIndex; i < boxSize; i++) {
			if (i == boxSize - 1) {
				text[i] = ' ';
				cout << text[i];
				break;
			}
			text[i] = text[i + 1];
			cout << text[i];
			COORD moveRight = { curserPosition + offset++ , startPoint.Y + 1 };
			SetConsoleCursorPosition(handle, moveRight);
		}
		COORD reset = { curserPosition , startPoint.Y + 1 };
		SetConsoleCursorPosition(handle, reset);
	}
	string tr33y = GetText();
	int x = 90;
}

void TextBox::AddCharecter(char c) {
	if (focus) {
		if (textIndex < boxSize) {
			text[textIndex] = c;
			cout << c;
			MoveRight();
		}
	}
}

string TextBox::GetText() {
	string str(text.begin(), text.end());
	return str;
}