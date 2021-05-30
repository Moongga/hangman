#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstring>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD position;

int curent_color = 7;

int startX = 40;
int startY = 19;
int margin_Y = 2;
int margin_X = 2;

COORD position_test = { startX, startY };

const int items_count = 26;
const int items_count_ru = 33;

string alphabet;

char* blacklist = new char[items_count];

int current_item_Y = 0;
int current_item_X = 0;

int word_index = 0;

string answer_word;
string game_word;
