#include "Label.h";

Label::Label(short width, short hieght, string text, bool isVisible) {
	cord = { width, hieght };
	labelText = text;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCursorEnable(isVisible);
}
void Label::SetCursorEnable(bool enable) {
	CONSOLE_CURSOR_INFO newCci = { 100, enable };
	SetConsoleCursorInfo(handle, &newCci);
}
void Label::SetColor(DWORD color) {
	dw = color;
	
}
void Label::SwitchContent(string newText) {
	labelText = newText;
	SetConsoleCursorPosition(handle, cord);
	Print();
}
COORD Label::GetCord() {
	return cord;
}
string Label::GetText() {
	return labelText;
}
DWORD Label::GetColor() {
	return dw;
}
void Label::Hoover(bool isHover) {
	if (isHover) {
		dw = (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) | dw;
		SetColor(dw);
		Print();
		return;
	}
	else {
		dw = ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) & dw;
		SetColor(dw);
		Print();
	}
	return;
}
void Label::Print() const {
	SetConsoleCursorPosition(handle, cord);
	SetConsoleTextAttribute(handle, dw);
	cout << labelText;
}
Label::~Label() {

}