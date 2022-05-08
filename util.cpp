#include "util.h"

namespace util {
    void win_record(int attempt_number, std::string name)
    {

        std::fstream file;
        file.open(path_fbase, std::fstream::in | std::fstream::out);

        std::string buf = "";

        Winner* rec_winer = new Winner(attempt_number, name);
        Winner* winner_buf;

        bool old_winner = false;
        std::streampos position = file.tellg();
        while (getline(file, buf))
        {
            winner_buf = parser_string(buf);
            if (winner_buf->get_name() == rec_winer->get_name())
            {
                old_winner = true;
                if (winner_buf->get_attempt_number() > rec_winer->get_attempt_number())
                {
                    file.seekp(position);
                    file << rec_winer->get_name() << divider << std::setw(5) << rec_winer->get_attempt_number() << std::endl;
                }
                delete winner_buf;
                break;
            }
            delete winner_buf;
            position = file.tellg();
        }
        file.close();
        if (!old_winner)
        {
            file.open(path_fbase, std::fstream::app);
            file << rec_winer->get_name() << divider << std::setw(5) << rec_winer->get_attempt_number() << std::endl;
            file.close();
        }
        delete rec_winer;
    }

    Winner* parser_string(std::string line)
    {
        int size = line.size();
        std::string name = "";
        std::string att = "";
        bool rec_att = false;
        for (int i = 0; i < size; i++)
        {
            if (line[i] == divider) {
                rec_att = true;
            }
            else if (!rec_att) {
                name += line[i];
            }
            else
            {
                att += line[i];
            }
        }
        Winner* winner = new Winner(stoi(att), name);
        return winner;
    }

    void print_table_winners()
    {
        std::list<Winner*> list_winners;
        std::fstream file;
        file.open(path_fbase, std::fstream::in);
        if (!file.is_open()) {
            std::cout << "table file not found" << std::endl;
            exit(1);
        }
        if (file)
        {
            std::string buf = "";
            while (getline(file, buf)) {
                list_winners.push_back(parser_string(buf));
            }
        }
        std::cout << "------------------------" << std::endl
            << "High scores table:" << std::endl;

        std::list <Winner*> ::iterator it;
        for (it = list_winners.begin(); it != list_winners.end(); it++)
        {
            std::cout << (*it)->get_name() << ":" << (*it)->get_attempt_number() << std::endl;
            delete (*it);
        }
        std::cout << "------------------------" << std::endl;
        file.close();
    }

    bool is_number(std::string word) {

        for (int i = 0; i < word.size(); i++)
        {
            if (!isdigit(word[i]))
            {
                return false;
            }
        }
        return true;
    }

    int get_max_value_from_lvl(int level)
    {
        if (level == 1)
        {
            return 10;
        }
        if (level == 2)
        {
            return 50;
        }
        if (level == 3)
        {
            return 100;
        }
        std::cout << "Incorrect parameter level. Level may be 1 or 2 or 3" << std::endl;
        exit(1);

    }

    void parse_parametrs_open(int argc, char** argv, int& max_value)
    {
        if (argc > 1) {
            if (std::string(argv[1]) == "-table")
            {
                print_table_winners();
                exit(0);
            }
            else if (std::string(argv[1]) == "-max")
            {
                if (!is_number(std::string(argv[2])))
                {
                    std::cout << "Incorrect parameter max. The parameter must be numeric" << std::endl;
                    exit(1);
                }
                max_value = stoi(std::string(argv[2]));
                for (int i = 2; i < argc; i++) {
                    if (std::string(argv[i]) == "-level") exit(1);
                }
            }
            else if (std::string(argv[1]) == "-level")
            {
                max_value = get_max_value_from_lvl(stoi(std::string(argv[2])));
                for (int i = 2; i < argc; i++) {
                    if (std::string(argv[i]) == "-max") exit(1);
                }
            }
        }
    }
}