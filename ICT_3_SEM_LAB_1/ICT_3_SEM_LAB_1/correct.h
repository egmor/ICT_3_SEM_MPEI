#ifndef CORRECT_H
#define CORRECT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <format>

struct Patient {
    std::string name{};
    std::string surname{};
    std::string last_name{};
};

struct Address {
    std::string city{};
    std::string district{};
    std::string street{};
    std::string building{};
    std::string apartment{};
};

struct Date_Last_Visit {
    unsigned int day{};
    unsigned int month{};
    unsigned int year{};
};

struct Medical_Record {
    Patient SNL{};
    Address address{};
    Date_Last_Visit date{};
    unsigned int birth_year{};
    std::string illness{};
};

bool correct_day(Date_Last_Visit date);
bool correct_date(Medical_Record& data);
bool correct_address(Address& data);
bool correct_name(Patient& data);

#endif //CORRECT_H