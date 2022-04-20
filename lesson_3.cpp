#include "winner.h"
#include "lesson_3.h"


void win_record(int attempt_number, std::string name)
{

    std::fstream file;
    file.open(path_fbase, std::fstream::in | std::fstream::out);// | std::fstream::app);

    std::string buf = "";

    Winner* rec_winer = new Winner(attempt_number, name);
    Winner* winner_buf;

    bool old_winner = false;
    std::streampos position = file.tellg();
    while (getline(file, buf))
    {
        winner_buf = parser_string(buf);
        if (winner_buf->name == rec_winer->name)
        {
            old_winner = true;
            if (winner_buf->attempt_number > rec_winer->attempt_number)
            {
                file.seekp(position);
                file << rec_winer->name << divider << std::setw(5) << rec_winer->attempt_number << std::endl;
            }
            delete winner_buf;
            break;
        }
        delete winner_buf;
        position = file.tellg();
    }
    file.close();//
    if (!old_winner)
    {
        //file.seekp(position);
        file.open(path_fbase, std::fstream::app);//
        file << rec_winer->name << divider << std::setw(5) << rec_winer->attempt_number << std::endl;
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
        std::cout << (*it)->name << ":" << (*it)->attempt_number << std::endl;
        delete (*it);
    }
    std::cout << "------------------------" << std::endl;
    file.close();
}

bool isNumber(std::string word) {

    for (int i = 0; i < word.size(); i++)
    {
        if (!isdigit(word[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    int max_value = 100;
    if (argc > 1) {
        if (std::string(argv[1]) == "-table")
        {
            print_table_winners();
            exit(0);
        }
        else if (std::string(argv[1]) == "-max")
        {
            max_value = stoi(std::string(argv[2]));
            for (int i = 2; i < argc; i++){
                if (std::string(argv[i]) == "-level") exit(1);
            }
        }
        else if (std::string(argv[1]) == "-level")
        {
            if (stoi(std::string(argv[2])) == 1)
            {
                max_value = 10;
            }
            else if (stoi(std::string(argv[2])) == 2)
            {
                max_value = 50;
            }
            else if (stoi(std::string(argv[2])) == 3)
            {
                max_value = 100;
            }
            for (int i = 2; i < argc; i++) {
                if (std::string(argv[i]) == "-max") exit(1);
            }
        }
    }
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::string name = "";
    std::cin >> name;
    while (true)
    {
        std::srand(unsigned int(std::time(nullptr)));
        const int random_value = std::rand() % max_value;
        std::cout << "Enter your guess: (To exit, write \"exit\")" << std::endl;
        int attempt_number = 0;
        std::string word = "";
        int number = 0;
        do
        {
            attempt_number++;
            std::cin >> word;
            if (word == "exit") exit(0);
            if (!isNumber(word)) {
                std::cout << "Please enter the number: " << std::endl;
                continue;
            }
            number = stoi(word);
            if (number == random_value) {
                std::cout << "you win! attempts = " << attempt_number << std::endl;
                win_record(attempt_number, name);
                print_table_winners();
                break;
            }
            else if (number > random_value) {
                std::cout << "less than " << number << std::endl;
            }
            else if (number < random_value) {
                std::cout << "greater than " << number << std::endl;
            }
        } while (true);
        std::cout << "Repeat (y/n):";
        std::string word_ex = "";
        std::cin >> word_ex;
        if (word_ex != "y") 
        {
            break;
        }
        system("cls");
    }
    //system("PAUSE");
}


