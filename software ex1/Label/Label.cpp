#include "Label.h";

Label::Label(short width, short highet, string text, CONSOLE_CURSOR_INFO _cci) {
	cord = { width, highet };
	labelText = text;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, cord);

	cci = _cci;
	SetConsoleCursorInfo(handle, &cci);
}
void Label::SetColor(DWORD color) {
	dw = color;
	SetConsoleTextAttribute(handle, dw);
}
void Label::Print() {
	cout << labelText << endl;
}
Label::~Label() {

}