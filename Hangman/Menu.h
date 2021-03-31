#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
#pragma comment(lib,"msimg32.lib")

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD position;

void DrawSymbol(int x, int y, int width, int height, int color1, int color2, int color3) {
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(color1, color2, color3));
	HBRUSH brush = CreateSolidBrush(RGB(color1, color2, color3));
	HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
	HDC hdc = GetDC(hwnd);
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, x, y, x + width, y + height);
	DeleteObject(pen);
	DeleteObject(brush);
}

void ShowMenu()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
	HDC hdc = GetDC(hwnd);
	system("title Hangman");
	system("mode con cols=100 lines=47");
	//Местоположение и размер консоли на экране
	
	// Выставление шрифта по умолчанию
	CONSOLE_FONT_INFOEX CFI;
	CFI.cbSize = sizeof CFI;
	CFI.nFont = 0;
	CFI.dwFontSize.X = 8; // ширина шрифта
	CFI.dwFontSize.Y = 12;  // высота шрифта
	CFI.FontFamily = FF_DONTCARE;
	CFI.FontWeight = FW_NORMAL;
	wcscpy_s(CFI.FaceName, L"Terminal"); //задаём шрифт по умолчанию (точечный)
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &CFI);
	//SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //запрещает раздвигать консоль в разные стороны
	
	//MoveWindow(GetConsoleWindow(), 540, 250, 900, 500, true); //Нужный размер консоли по ширине, высоте, местаположение консоли
	
	//белый фон
	
	DrawSymbol(0, 0, 2000, 2000, 255, 255, 255);
	
	//h
	DrawSymbol(50, 60, 30, 150, 128, 128, 128);
	
	
	//h
	DrawSymbol(150, 60, 30, 150, 128, 128, 128);
	
	//h
	DrawSymbol(51, 120, 100, 25, 128, 128, 128);
	
	//a
	int left_shift = 250;
	int top_shift = 60;
	int width = 50;
	int height = 50;
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	HBRUSH brush = CreateSolidBrush(RGB(128, 128, 128));
	//HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
	//HDC hdc = GetDC(hwnd);
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, left_shift, top_shift, left_shift + width, top_shift + height);
	DeleteObject(pen);
	DeleteObject(brush);
	
	
	
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);
	Sleep(INFINITE);
}
