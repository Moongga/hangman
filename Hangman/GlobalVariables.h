#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstring>

string answer_word;
string game_word = GetWord();
int words_amount = game_word.length();
int words_left = words_amount;