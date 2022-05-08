#include "main.h"



int main(int argc, char** argv)
{
    Game* game = Game::get_instance();
    
    int max_value = game->get_max_value();
    util::parse_parametrs_open(argc, argv, max_value);
    
    
    game->set_max_value(max_value);
    game->welcome();
    while (true)
    {
        game->init_random_value();
        game->print_first_line_game();
        game->new_counter();
        do
        {
            game->counter();
            if (!game->check_input())
            {
                continue;
            }
            if (game->guessed())
            {
                break;
            }
            game->number_less_or_greater();
        } while (true);
        if (!game->user_continue()) break;
        system("cls");
    }
}


