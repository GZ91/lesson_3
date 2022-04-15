#include "winner.h"
#include "lesson_3.h"


void win_record(int attempt_number, string name)
{
    std::list<Winner*> list_winners;
    list_winners.push_back(new Winner(attempt_number, name));
    std::fstream file_r;
    file_r.open(PATH_FBASE, std::fstream::in);
    string buf = "";
    while (getline(file_r, buf))
    {
        list_winners.push_back(parser_string(buf));
    }
    filter_winners(list_winners);
    file_r.close();


    std::ofstream file;
    file.open(PATH_FBASE, std::ofstream::out);
    std::list <Winner*> ::iterator it;
    for (it = list_winners.begin(); it != list_winners.end(); it++)
    {
        file << (*it)->name << DIVIDER << (*it)->attempt_number << endl;
        delete (*it);
    } 
    file.close();
}

Winner* parser_string(string line)
{
    int size = line.size();
    string name = "";
    string att = "";
    bool rec_att = false;
    for (int i = 0; i < size; i++)
    {
        if (line[i] == DIVIDER) {
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

void filter_winners(std::list<Winner*> &list_winners)
{
    list_winners.sort([](Winner* winner1, Winner* winner2) {return winner1->name < winner2->name;  });
    list_winners.sort([](Winner* winner1, Winner* winner2) {return winner1->attempt_number < winner2->attempt_number && winner1->name == winner2->name; });
    std::list <Winner*> ::iterator it;
    string buf_name = "";

    it = list_winners.begin();
    bool cont = true;
    while (true)
    {  
        if (it == list_winners.end())
        {
            break;
        }
        if ((*it)->name != buf_name)
        {
            buf_name = (*it)->name;
            it++;
            continue;
        }
        delete (*it);
        list_winners.erase(it++);
    }
    list_winners.sort([](Winner* winner1, Winner* winner2) {return winner1->attempt_number < winner2->attempt_number;  });
}

void print_table_winners()
{
    std::list<Winner*> list_winners;
    std::fstream file;
    file.open(PATH_FBASE, std::fstream::in);
    if (!file.is_open()) {
        cout << "table file not found" << endl;
        exit(1);
    }
    if (file)
    {
        string buf = "";
        while (getline(file, buf)) {
            list_winners.push_back(parser_string(buf));
        }
    }
    //filter_winners(list_winners);
    cout << "------------------------" << endl 
        << "High scores table:" << endl;

    std::list <Winner*> ::iterator it;
    for (it = list_winners.begin(); it != list_winners.end(); it++)
    {
        cout << (*it)->name << ":" << (*it)->attempt_number << endl;
        delete (*it);
    }
    cout << "------------------------" << endl;
    file.close();
}

bool isNumber(string word) {

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
        if (string(argv[1]) == "-table")
        {
            print_table_winners();
            exit(0);
        }
        else if (string(argv[1]) == "-max")
        {
            max_value = stoi(string(argv[2]));
            for (int i = 2; i < argc; i++){
                if (string(argv[i]) == "-level") exit(1);
            }
        }
        else if (string(argv[1]) == "-level")
        {
            if (stoi(string(argv[2])) == 1)
            {
                max_value = 10;
            }
            else if (stoi(string(argv[2])) == 2)
            {
                max_value = 50;
            }
            else if (stoi(string(argv[2])) == 3)
            {
                max_value = 100;
            }
            for (int i = 2; i < argc; i++) {
                if (string(argv[i]) == "-max") exit(1);
            }
        }
    }
    cout << "Hi! Enter your name, please:" << endl;
    string name = "";
    cin >> name;
    while (true)
    {
        std::srand(unsigned int(std::time(nullptr)));
        const int random_value = std::rand() % max_value;
        cout << "Enter your guess: (To exit, write \"exit\")" << endl;
        int attempt_number = 0;
        string word = "";
        int number = 0;
        do
        {
            attempt_number++;
            cin >> word;
            if (word == "exit") exit(0);
            if (!isNumber(word)) {
                cout << "Please enter the number: " << endl;
                continue;
            }
            number = stoi(word);
            if (number == random_value) {
                cout << "you win! attempts = " << attempt_number << endl;
                win_record(attempt_number, name);
                print_table_winners();
                break;
            }
            else if (number > random_value) {
                cout << "less than " << number << endl;
            }
            else if (number < random_value) {
                cout << "greater than " << number << endl;
            }
        } while (true);
        cout << "Repeat (y/n):";
        string word_ex = "";
        cin >> word_ex;
        if (word_ex != "y") 
        {
            break;
        }
        system("cls");
    }
    //system("PAUSE");
}


