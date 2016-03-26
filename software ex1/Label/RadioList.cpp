#include "RadioList.h"



RadioList::RadioList(string* textList, int listSize, short width, short hieght, DWORD color) : 
	CheckList(textList, listSize, width, hieght, color) {

}

void RadioList::Mark() {
	if (chosen[currentRow]) {
		string newText = list[currentRow].GetText();
		newText[1] = ' ';
		COORD newCoord = list[currentRow].GetCord();
		DWORD color = list[currentRow].GetColor();
		list[currentRow] = Label(newCoord.X, newCoord.Y, newText, false);
		list[currentRow].SetColor(color);
		chosen[currentRow] = false;
	}
	else {
		int oldChoice = -1;
		for (int i = 0; i < list.size(); i++) {
			if (chosen[i]) {
				oldChoice = i;
				chosen[i] = false;
				break;
			}
		}
		if (oldChoice != -1) {
			string unmark = list[oldChoice].GetText();
			unmark[1] = ' ';
			COORD unmarkCoord = list[oldChoice].GetCord();
			DWORD unmarkcolor = list[oldChoice].GetColor();
			list[oldChoice] = Label(unmarkCoord.X, unmarkCoord.Y, unmark, false);
			list[oldChoice].SetColor(unmarkcolor);
			list[oldChoice].Print();
		}
		//new chosen raw
		string newText = list[currentRow].GetText();
		newText[1] = 'X';
		COORD newCoord = list[currentRow].GetCord();
		DWORD color = list[currentRow].GetColor();
		list[currentRow] = Label(newCoord.X, newCoord.Y, newText, false);
		list[currentRow].SetColor(color);
		chosen[currentRow] = true;
	}
	list[currentRow].Print();
	return;
}

int RadioList::LongestOptios() {
	int size = 0;
	for (int i = 0; i < list.size(); i++) {
		if (size <= list[i].Length()) size = list[i].Length();
	}
	return size;
}

string RadioList::GetChosen() {
	int index = 0;
	bool flage = false;
	for (index; index < list.size(); index++) {
		if (chosen[index]) {
			flage = true;
			break;
		}
	}
	if (!flage) return "no choose";
	return list[index].GetText();
}

RadioList::~RadioList(){

}
