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

void ShowAlphabet() {
	enum Keys { ENTER = 13, ESCAPE = 27, SPACE = 32, LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };

	const int items_count = 26;
	string menu_items[items_count] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
		"k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

	//SetCursor(40, 14);

	int startX = 40;
	int startY = 11;
	int margin_Y = 2;
	int margin_X = 2;

	COORD position_test = { startX, startY };

	for (int i = 0; i < 26; i++)
	{
		if (i == 13)
		{
			position_test.Y += margin_Y;
			position_test.X = startX;
		}
		SetConsoleTextAttribute(h, 7);
		SetConsoleCursorPosition(h, position_test);
		cout << menu_items[i];
		position_test.X += margin_X;
	}

	int current_item_Y = 0;
	int current_item_X = 0;

	int word_index = 0;

	//int current_item = 0; // первая буква
	SetCursor(startX, startY);

	SetConsoleTextAttribute(h, 14);
	position_test.Y = startY + current_item_Y * margin_Y;
	position_test.X = startX + current_item_X * margin_X;
	SetConsoleCursorPosition(h, position);
	cout << menu_items[current_item_Y + current_item_X];

	int code;
	while (true)
	{
		code = _getch();
		if (code == 224)
			code = _getch();

		
		SetConsoleTextAttribute(h, 7);
		position_test.Y = startY + current_item_Y * margin_Y;
		position_test.X = startX + current_item_X * margin_X;
		SetConsoleCursorPosition(h, position_test);
		cout << menu_items[current_item_Y + current_item_X];

		if ((code == DOWN) && current_item_Y < margin_Y - 1) // down arrow
		{
			current_item_Y++;
		}
		else if ((code == UP) && current_item_Y > 0) // up arrow
		{
			current_item_Y--;
		}
		/*else if (code == ENTER)
		{
			switch (current_item)
			{
			case 0:
				new_game();
				break;
			case 1:
				load_game();
				break;
			case 2:
				game_options();
				break;
			case 3:
				about_author();
				break;
			default:
				exit(0);
				break;
			}*/
		//}

		SetConsoleTextAttribute(h, 14);
		position_test.Y = startY + current_item_Y * margin_Y;
		SetConsoleCursorPosition(h, position_test);
		cout << menu_items[13 + current_item_X];

	}
}

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


	ShowAlphabet();

	//генерация случайного игрового слова из списка
	string game_word = GetWord();

	//отдельная переменная для подсчёта количества букв в слове чтобы нарисовать прочерки (неотгаданные буквы)
	int words_amount = game_word.length();

	SetCursor(40, 3);
	for (int i = 0; i < words_amount - 1; i++)
	{
		cout << "_ ";
	}

	words_amount--;

	int tries = 6;

	SetCursor(40, 8);
	cout << "Осталось попыток: " << tries;

	string answer_word;
	SetCursor(40, 4);
	cout << "Попробуйте отгадать букву: ";
	
	cin >> answer_word;

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