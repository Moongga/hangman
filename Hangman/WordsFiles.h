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

	setlocale(LC_ALL, "�");

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

	//fopen_s(&f, "Words.txt", "r"); // ��������� ��� �� ������
	fopen_s(&f, path, "r"); // ��������� ��� �� ������

	//int n = 364; // ���������� ����� � �����
	int n = 65;

	int random = rand() % n + 1;

	char random_word [200];

	for (int i = 0; i < random; i++)
	{
		fgets(random_word, 200, f); // ��������� ������
		//AnsiToOem(random_word, random_word); // ��������� ���������
	}

	fclose(f);
	setlocale(LC_ALL, "RUS");
	return random_word;
}