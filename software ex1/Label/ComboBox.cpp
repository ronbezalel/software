#include "ComboBox.h"



ComboBox::ComboBox(string* textList, int size, short width, short hieght, DWORD color) 
{	
	listSize = size;
	chosenText = new Label(width, hieght, "+ chose 1 option:", false);
	DWORD dw = BACKGROUND_BLUE && color;
	chosenText->SetColor(dw);
	optionsList = new RadioList(textList, listSize, width, hieght+2, color);
	EraseList();
}

void ComboBox::PrintComboBox() {
	chosenText->Print();
	//optionsList->Print();
}

void ComboBox::KeyEventProc(KEY_EVENT_RECORD ker) {
	optionsList->KeyEventProc(ker);
	string chose = optionsList->GetChosen();
	chosenText->SwitchContent(chose);
}
void ComboBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
	if (displayList) {
		if (checkPosition(mer) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			displayList = false;
			EraseList();
			string plus = optionsList->GetChosen();
			if (plus != "no choose") {
				plus[0] = '+';
				plus[1] = ' ';
				plus[2] = ' ';
			}
			else {
				plus = "+ " + plus;
			}
			chosenText->CleanLabel();
			chosenText->SwitchContent(plus);
			return;
		}
		optionsList->MouseEventProc(mer);
		string chose = optionsList->GetChosen();
		chosenText->CleanLabel();
		if (chose != "no choose") {
			chose[0] = '-';
			chose[1] = ' ';
			chose[2] = ' ';
		}
		else {
			chose = "- chose 1 option:";
		}
		chosenText->SwitchContent(chose);
	}
	else {
		if (checkPosition(mer) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			displayList = true;
			optionsList->Print();
		}
	}
}

void ComboBox::EraseList() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dw = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetConsoleTextAttribute(handle, dw);
	COORD crd = { chosenText->GetCord().X , chosenText->GetCord().Y + 2 };
	SetConsoleCursorPosition(handle, crd);
	int maxLength = optionsList->LongestOptios();
	for (short i = crd.Y; i < crd.Y + listSize ; i++) {
		for (short j = crd.X; j < crd.X + maxLength; j++) {
			COORD tmpCrd = { j , i };
			SetConsoleCursorPosition(handle, tmpCrd);
			cout << " ";
		}
	}
}

void ComboBox::HandleInput(INPUT_RECORD iRecord) {
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

bool ComboBox::checkPosition(MOUSE_EVENT_RECORD mer) {
	if (mer.dwMousePosition.X == chosenText->GetCord().X &&
		mer.dwMousePosition.Y == chosenText->GetCord().Y) {
		return true;
	}
	return false;
}


ComboBox::~ComboBox() {
	delete(chosenText);
	delete(optionsList);
}
