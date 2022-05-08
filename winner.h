#pragma once

#include <string>

class Winner
{
public:
    Winner(int att, std::string _name);
    int get_attempt_number() const { return attempt_number; }
    void set_attempt_number(int _) { attempt_number = _; }
    std::string get_name() const { return name; }
    void set_name(std::string _) { name = _; }
private:
    std::string name;
    int attempt_number;
};

