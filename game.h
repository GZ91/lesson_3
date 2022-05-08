#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "winner.h"
#include "util.h"


class Game //implemented with a singleton
{
public:
	static Game* get_instance();
	void welcome();
	void init_random_value();
	int get_max_value() { return max_value; };
	void set_max_value(int _) { max_value = _; };
	void new_counter();
	void counter();
	int get_counter();
	bool check_input();
	bool guessed();
	void number_less_or_greater();
	void print_first_line_game();
	bool user_continue();
private:
	static Game* game_instance;
	Game() {}
	Game(const Game&);
	Game& operator=(Game&);

	int max_value = 100;
	int attempt_number = 0;
	std::string word = "";
	int number = 0;
	int random_value = 0;
	std::string name = "";
};
