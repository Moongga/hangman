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

	// ���������� ����� � �����
	int n;

	if (which_path)
	{
		strcpy(path, "Words_Ru.txt");
		n = 65;
	}
	else
	{
		strcpy(path, "Words_Eng.txt");
		n = 364;
	}

	FILE* f;

	fopen_s(&f, path, "r"); // ��������� ��� �� ������

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