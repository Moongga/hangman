#include <iostream>
#include <conio.h> // _getch
#include <windows.h> // ShellExecuteA
#include <ctime>
using namespace std;

bool which_path;

string GetWord()
{
	srand(time(0));
	rand();

	setlocale(LC_ALL, "С");

	char path [256];

	if (which_path)
	{
		strcpy(path, "Words_Ru.txt");
	}
	else
	{
		strcpy(path, "Words_Eng.txt");
	}

	FILE* f;

	//fopen_s(&f, "Words.txt", "r"); // открываем его на чтение
	fopen_s(&f, path, "r"); // открываем его на чтение

	//int n = 364; // количество строк в файле
	int n = 65;

	int random = rand() % n + 1;

	char random_word [200];

	for (int i = 0; i < random; i++)
	{
		fgets(random_word, 200, f); // считываем строку
		//AnsiToOem(random_word, random_word); // переводим кодировку
	}

	fclose(f);
	setlocale(LC_ALL, "RUS");
	return random_word;
}