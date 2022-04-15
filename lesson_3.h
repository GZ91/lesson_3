#pragma once
#include <iostream>
#include <time.h>
#include <ctime>
#include <string>
#include <fstream>
#include <list>

#define DIVIDER '*'
#define PATH_FBASE "winner_table.txt"

const int max_value = 100;

using std::cout;
using std::endl;
using std::cin;
using std::string;

Winner* parser_string(string);
void filter_winners(std::list<Winner*>&);
void win_record(int, string);
Winner* parser_string(string);
void print_table_winners();
bool isNumber(string);