#pragma once
#include <string>
#include "winner.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

namespace util {

	const std::string path_fbase = "winner_table.txt";
	const char divider = '*';
	
	void win_record(int, std::string);
	Winner* parser_string(std::string);
	void print_table_winners();
	bool is_number(std::string);
	void parse_parametrs_open(int, char**, int&);
	int get_max_value_from_lvl(int);
	
}