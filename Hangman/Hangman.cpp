#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstring>
#include "Menu.h"
#include "WordsFiles.h"

using namespace std;

void SetCursor(int x, int y) {
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(h, position);
}

//void ShowAlphabet() {
//	const int items_count = 26;
//	string menu_items[items_count] = { "abcdefghijklmnopqrstuvwxyz" };
//
//	for (int i = 0; i < 13; i++)
//	{
//		cout << menu_items[i] << " ";
//	}
//
//	position.Y++;
//
//	for (int i = 13; i < 26; i++)
//	{
//		cout << menu_items[i] << " ";
//	}
//}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Выставление шрифта по умолчанию
	CONSOLE_FONT_INFOEX CFI;
	CFI.cbSize = sizeof CFI;
	CFI.nFont = 0;
	CFI.dwFontSize.X = 12; // ширина шрифта
	CFI.dwFontSize.Y = 14;  // высота шрифта
	CFI.FontFamily = FF_DONTCARE;
	CFI.FontWeight = FW_NORMAL;
	wcscpy_s(CFI.FaceName, L"Lucida Console"); //задаём шрифт по умолчанию (Lucida Console)
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &CFI);

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 100;
	SetConsoleCursorInfo(h, &cursor);

	system("title Hangman");

	//system("mode con cols=80 lines=50");

	enum Colors { DARK_RED = 4, RED = 12 };
	enum Keys { ENTER = 13, ESCAPE = 27, SPACE = 32, LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };

	srand(time(0));
	rand();

	setlocale(0, "RUS");

	SetCursor(10, 2);
	cout << " ---";
	SetCursor(10, 3);
	for (int i = 0; i < 4; i++)
	{
		cout << "|";
		position.Y++;
		SetConsoleCursorPosition(h, position);
	}

	SetCursor(10, 7);

	cout << "----";

	SetCursor(40, 10);
	cout << "На каком языке Вы хотите отгадывать?";
	SetCursor(40, 11);
	cout << "(на русском - 1, на английском - 2): ";
	int answer_language;

	cin >> answer_language;

	if (answer_language == 1)
	{
		which_path = true;
	}
	else if (answer_language == 2)
	{
		which_path = false;
	}

	// Чистим текст
	SetCursor(40, 10);
	for (int new_line = 0; new_line < 2; new_line++)
	{
		for (int i = 0; i < 38; i++)
		{
			cout << " ";
			position.X++;
			SetConsoleCursorPosition(h, position);
		}
		SetCursor(40, 11);
	}

	//SetCursor(40, 14);
	//ShowAlphabet();

	//генерация случайного игрового слова из списка
	string game_word = GetWord();

	//отдельная переменная для подсчёта количества букв в слове чтобы нарисовать прочерки (неотгаданные буквы)
	int words_amount = game_word.length();

	SetCursor(40, 3);
	for (int i = 0; i < words_amount - 1; i++)
	{
		cout << "_ ";
	}

	int tries = 6;

	SetCursor(40, 8);
	cout << "Осталось попыток: " << tries;

	string answer_word;
	SetCursor(40, 4);
	cout << "Попробуйте отгадать букву: ";
	
	cin >> answer_word;
	setlocale(0, "C");
	cout << " " << answer_word;

	// количество слов, которых осталось отгадать пользователю
	int words_left = words_amount;

	while (words_left > 0) {
		if (tries > 0)
		{
			position.Y = 3;

			// переменная для выявления, отгадал ли пользователь букву, или нет (в таком случае рисуется часть человечка)
			int comparate = words_left;
			for (int i = 0; i < words_amount; i++)
			{
				if (answer_word[0] == game_word[i])
				{
					position.X = i * 2 + 40;
					SetConsoleCursorPosition(h, position);
					cout << answer_word[0];
					words_left--;
				}
			}

			// Если переменные равны, значит входа в цикл не было (и переменная words_left не снижалась), в следствии чего буква не была отгадана
			if (comparate == words_left)
			{
				tries--;
				if (tries == 5)
				{
					SetCursor(13, 3);
					cout << "o";
				}
				if (tries == 4)
				{
					SetCursor(13, 4);
					cout << "|";
				}
				if (tries == 3)
				{
					SetCursor(12, 4);
					cout << "/";
				}
				if (tries == 2)
				{
					SetCursor(14, 4);
					cout << "\\";
				}
				if (tries == 1)
				{
					SetCursor(12, 5);
					cout << "/";
				}
				if (tries == 0)
				{
					SetCursor(14, 5);
					cout << "\\";
				}

				SetCursor(40, 8);
				cout << "Осталось попыток: " << tries;
			}

			SetCursor(67, 4);

			// если попытки закончились, то поражение
			if (tries == 0)
			{
				SetCursor(40, 7);
				cout << "К сожалению, вы проиграли, ";
				SetCursor(40, 8);
				cout << "но загаданное слово было: " << game_word << "\n";
				break;
			}

			// если все слова отгаданы, то победа
			if (words_left == 0 && tries > 0)
			{
				SetCursor(40, 8);
				cout << "Поздравляем, Вы выиграли!\n";
				break;
			}
			cin >> answer_word;
		}
	}
}