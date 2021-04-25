#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstring>

int curent_color = 7;

int startX = 40;
int startY = 19;
int margin_Y = 2;
int margin_X = 2;

COORD position_test = { startX, startY };

const int items_count = 26;
const int items_count_ru = 33;

string alphabet;

//string menu_items[items_count] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
//	"k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

//string menu_ruitems[items_count] = { "à", "á", "â", "ã", "ä", "å", "¸", "æ", "ç", "è",
//	"é", "ê", "ë", "ì", "í", "î", "ï", "ð", "ñ", "ò", "ó", "ô", "õ", "ö", "÷", "ø" };


int current_item_Y = 0;
int current_item_X = 0;

int word_index = 0;

string answer_word;
string game_word;
