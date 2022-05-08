#include "game.h"

void Game::welcome()
{
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::cin >> name;
    system("cls");
}

void Game::init_random_value()
{
    std::srand(unsigned int(std::time(nullptr)));
    random_value = std::rand() % max_value;
}

void Game::new_counter()
{
    attempt_number = 0;
}

void Game::counter()
{
    attempt_number++;
}

int Game::get_counter()
{
    return attempt_number;
}

bool Game::check_input()
{
    std::cin >> word;
    if (word == "exit") exit(0);
    if (!util::is_number(word)) {
        std::cout << "Please enter the number: " << std::endl;
        return false;
    }
    number = stoi(word);
    return true;
}

bool Game::guessed()
{
    if (number == random_value) {
        std::cout << "you win! attempts = " << get_counter() << std::endl;
        util::win_record(get_counter(), name);
        util::print_table_winners();
        return true;
    }
    return false;
}

void Game::number_less_or_greater()
{
    if (number > random_value)
        std::cout << "less than " << number << std::endl;
    else
        std::cout << "greater than " << number << std::endl;
}

void Game::print_first_line_game()
{
    std::cout << "Enter your guess: (To exit, write \"exit\")" << std::endl;
}

bool Game::user_continue()
{
    std::cout << "Repeat (y/n):";
    std::string word_ex = "";
    std::cin >> word_ex;
    return word_ex == "y";
}

Game* Game::get_instance()
{
    if (game_instance == nullptr)
    {
        game_instance = new Game();
    }

    return game_instance;
}