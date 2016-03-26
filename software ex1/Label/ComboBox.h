#include "RadioList.h"
#include "Label.h"

class ComboBox
{
private:
	Label* chosenText;
	RadioList* optionsList;
	bool displayList = false;

	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);

public:
	ComboBox(string* textList, int listSize, short width, short hieght, DWORD color);
	~ComboBox();
	void PrintComboBox();
	void HandleInput(INPUT_RECORD iRecord);

};

