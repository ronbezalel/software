#include "ComboBox.h"



ComboBox::ComboBox(string* textList, int listSize, short width, short hieght, DWORD color) 
{	
	chosenText = new Label(width, hieght, "chose 1 option:", false);
	DWORD dw = BACKGROUND_BLUE && color;
	chosenText->SetColor(dw);
	optionsList = new RadioList(textList, listSize, width, hieght+2, color);
}

void ComboBox::PrintComboBox() {
	chosenText->Print();
	optionsList->Print();
}

void ComboBox::KeyEventProc(KEY_EVENT_RECORD ker) {
	optionsList->KeyEventProc(ker);
	string chose = optionsList->GetChosen();
	chosenText->SwitchContent(chose);
}
void ComboBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
	optionsList->MouseEventProc(mer);
	string chose = optionsList->GetChosen();
	chosenText->CleanLabel();
	if (chose != "no choose") {
		chose[0] = ' ';
		chose[1] = ' ';
		chose[2] = ' ';
	}
	else {
		chose = "chose 1 option:";
	}
	chosenText->SwitchContent(chose);
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


ComboBox::~ComboBox()
{
	delete(chosenText);
	delete(optionsList);
}
