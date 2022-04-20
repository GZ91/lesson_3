#pragma once
#include <iostream>
#include <time.h>
#include <ctime>
#include <string>
#include <fstream>
#include <list>
#include <iomanip>


const char divider = '*';
const std::string path_fbase = "winner_table.txt";

void filter_winners(std::list<Winner*>&);
void win_record(int, std::string);
Winner* parser_string(std::string);
void print_table_winners();
bool isNumber(std::string);