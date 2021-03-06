#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstring>
#include "WordsFiles.h"
#include "GlobalVariables.h"
using namespace std;

//////
int words_amount;
int words_left;
//////

// проверка буквы в чёрном списке
bool CheckBlacklist(int alph_amount, int steps) {
	for (int i = 0; i < alph_amount; i++)
	{
		if (blacklist[i] == alphabet[word_index + steps])
		{
			return false;
			break;
		}
	}
}

void SetCursor(int x, int y) {
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(h, position);
}

// проверяем букву на правильность/неправильность, чтобы потом окрасить в красный или зелёный
bool RightWord(int index = 0) {
	for (int i = 0; i < words_amount; i++) {
		if (alphabet[index] == game_word[i])
		{
			return true;
		}
	}
	return false;
}

// выводим алфавит-клавиатуру
void ShowAlphabet() {
	for (int i = 0; i < alphabet.size(); i++) {
		if (i == 13)
		{
			position_test.Y += margin_Y;
			position_test.X = startX;
		}
		if (i == 26)
		{
			position_test.Y += margin_Y;
			position_test.X = startX + 6;
		}
		SetConsoleTextAttribute(h, 7);
		SetConsoleCursorPosition(h, position_test);
		cout << alphabet[i];
		position_test.X += margin_X;
	}

	SetCursor(startX, startY);
	SetConsoleTextAttribute(h, 14);
	position_test.Y = startY + current_item_Y * margin_Y;
	position_test.X = startX + current_item_X * margin_X;
	SetConsoleCursorPosition(h, position);
	cout << alphabet[word_index];
}

// перемещение по клавиатуре
void MoveAlphabet() {
	enum Keys { ENTER = 13, ESCAPE = 27, SPACE = 32, LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
	int code;

	while (true)
	{
		string comparate = answer_word;
		// переменная, отвечающая за нажатие пользователем на Enter
		bool comparate_enter = true;

		// в отдельную переменную записываем, сколько в том или ином алфавите букв для сравнения в code == ENTER
		int alph_amount;
		if (which_path)
		{
			alph_amount = 33;
		}
		else if (!which_path)
		{
			alph_amount = 26;
		}

		// Если выбран русский язык, то благодаря переменной сможем передвигаться по трём столбцам клавиатуры (32 буквам),
		// если английский, то по двум столбцам (26 буквам)
		int which_margin;
		if (which_path)
		{

			which_margin = margin_Y;
		}
		else
		{
			which_margin = 1;
		}

		code = _getch();
		if (code == 224) {
			code = _getch();
		}

		SetConsoleTextAttribute(h, curent_color);
		position_test.Y = startY + current_item_Y * margin_Y;
		position_test.X = startX + current_item_X * margin_X;
		SetConsoleCursorPosition(h, position_test);
		cout << alphabet[word_index];

		// переменная для выявления, можно ли передвигаться на следующую клетку, или нет (в случае если она красная/зелёная)
		bool move_block = true;

		if ((code == DOWN))
		{
			if (!which_path && current_item_Y < which_margin)
			{
				if (CheckBlacklist(alph_amount, 13))
				{
					current_item_Y++;
					word_index += 13;
				}
			}

			if (which_path && (word_index > 15 && word_index < 23) && current_item_Y < which_margin)
			{
				current_item_Y++;
				word_index += 10;
			}
			else if (which_path && word_index < 13 && current_item_Y < which_margin)
			{
				current_item_Y++;
				word_index += 13;
			}
		}

		else if ((code == UP))
		{
			if (!which_path && current_item_Y > 0)
			{
				if (CheckBlacklist(alph_amount, -13)) {
					current_item_Y--;
					word_index -= 13;
				}
			}

			if (which_path && (word_index > 25 && word_index < 33) && current_item_Y > 0)
			{
				current_item_Y--;
				word_index -= 10;
			}
			else if (which_path && word_index < 26 && current_item_Y > 0)
			{
				current_item_Y--;
				word_index -= 13;
			}
		}

		if ((code == RIGHT))
		{
			if (!which_path && current_item_X < 12)
			{
				current_item_X++;
				word_index++;
			}

			if (which_path && (word_index > 25 && word_index < 32) && current_item_X < 10)
			{
				current_item_X++;
				word_index++;
			}

			else if (which_path && (word_index < 25) && (current_item_X < 12))
			{
				current_item_X++;
				word_index++;
			}
		}

		else if (code == LEFT)
		{
			if (!which_path && current_item_X > 0)
			{
				current_item_X--;
				word_index--;
			}

			if (which_path && word_index > 25 && current_item_X > 3)
			{
				current_item_X--;
				word_index--;
			}

			else if (which_path && word_index < 26 && current_item_X > 0)
			{
				current_item_X--;
				word_index--;
			}
		}

		else if (code == ENTER)
		{
			// записываем букву пользователя в переменную
			for (int i = 0; i < alph_amount; i++)
			{
				if (i == word_index)
				{
					answer_word = alphabet[word_index];
					break;
				}
			}

			// записываем букву пользователя в чёрный список
			for (int i = 0; i < alph_amount; i++)
			{
				if (blacklist[i] == 0)
				{
					blacklist[i] = alphabet[word_index];
					break;
				}
			}

			comparate_enter = false;

			if (RightWord(word_index))
			{

				curent_color = 10;
				SetConsoleCursorPosition(h, position_test);
				SetConsoleTextAttribute(h, 10);
				cout << alphabet[word_index];
			}
			else if (!RightWord(word_index)) {

				curent_color = 12;
				SetConsoleCursorPosition(h, position_test);
				SetConsoleTextAttribute(h, 12);
				cout << alphabet[word_index];
			}
		}

		if (comparate_enter)
		{
			curent_color = 7;
			SetConsoleTextAttribute(h, 14);
			position_test.Y = startY + current_item_Y * margin_Y;
			position_test.X = startX + current_item_X * margin_X;
			SetConsoleCursorPosition(h, position_test);
			cout << alphabet[word_index];
		}

		if (comparate != answer_word)
		{
			break;
		}
	}
}

void main()
{

	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

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

	setlocale(LC_ALL, "С");
	//setlocale(0, "RUS");

	for (int i = 0; i < items_count; i++)
	{
		blacklist[i] = 0;
	}

	int hangman_Xposition = 20;
	int hangman_Yposition = 14;
	int words_Yposition = startY - 6;

	SetConsoleTextAttribute(h, 7);
	SetCursor(hangman_Xposition - 2, hangman_Yposition);
	cout << (char)218 << (char)196 << (char)196 << (char)196;
	SetCursor(hangman_Xposition - 2, hangman_Yposition + 1);
	for (int i = 0; i < 4; i++)
	{
		cout << (char)179;
		position.Y++;
		SetConsoleCursorPosition(h, position);
	}

	SetCursor(hangman_Xposition - 2, hangman_Yposition + 5);

	cout << char(193) << (char)196;

	setlocale(0, "RUS");

	SetCursor(40, 19);
	cout << "На каком языке Вы хотите отгадывать?";
	SetCursor(40, 20);
	cout << "(на русском - 1, на английском - 2): ";
	int answer_language;

	cin >> answer_language;

	if (answer_language == 1) // на русском
	{
		which_path = true;
		alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	}

	else if (answer_language == 2) // на английском
	{
		which_path = false;
		alphabet = "abcdefghijklmnopqrstuvwxyz";
	}

	game_word = GetWord();
	words_amount = game_word.length();
	words_left = words_amount;

	// Чистим текст
	SetCursor(40, 19);
	for (int new_line = 0; new_line < 2; new_line++)
	{
		for (int i = 0; i < 38; i++)
		{
			cout << " ";
			position.X++;
			SetConsoleCursorPosition(h, position);
		}
		SetCursor(40, 20);
	}

	SetCursor(40, words_Yposition);
	for (int i = 0; i < words_amount - 1; i++)
	{
		cout << "_ ";
	}

	words_amount--;
	words_left--;

	int tries = 6;

	ShowAlphabet();
	MoveAlphabet();

	while (words_left > 0) {
		SetConsoleTextAttribute(h, 14);
		if (tries > 0)
		{
			position.Y = words_Yposition;

			// Переменная для выявления, отгадал ли пользователь букву, или нет (в таком случае рисуется часть человечка)
			int comparate = words_left;

			// Проверяем букву пользователя
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
					SetCursor(hangman_Xposition + 1, hangman_Yposition + 1);
					cout << "o";
				}
				if (tries == 4)
				{
					SetCursor(hangman_Xposition + 1, hangman_Yposition + 2);
					cout << "|";
				}
				if (tries == 3)
				{
					SetCursor(hangman_Xposition, hangman_Yposition + 2);
					cout << "/";
				}
				if (tries == 2)
				{
					SetCursor(hangman_Xposition + 2, hangman_Yposition + 2);
					cout << "\\";
				}
				if (tries == 1)
				{
					SetCursor(hangman_Xposition, hangman_Yposition + 3);
					cout << "/";
				}
				if (tries == 0)
				{
					SetCursor(hangman_Xposition + 2, hangman_Yposition + 3);
					cout << "\\";
				}
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
			SetCursor(40, 4);
			MoveAlphabet();
		}
	}
	delete[] blacklist;
}