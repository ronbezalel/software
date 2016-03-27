#include "RadioList.h"
#include "Label.h"

class ComboBox
{
private:
	Label* chosenText;
	RadioList* optionsList;
	bool displayList = false;
	int listSize;

	void EraseList();
	void KeyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	bool checkPosition(MOUSE_EVENT_RECORD mer);

public:
	ComboBox(string* textList, int size, short width, short hieght, DWORD color);
	~ComboBox();
	void PrintComboBox();
	void HandleInput(INPUT_RECORD iRecord);

};

