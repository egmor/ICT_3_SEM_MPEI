#include "correct.h"

bool correct_day(int day, int month, int year) {
    if (day > 31 || day < 1) return false;
    else if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) return false;
    else if (day > 29 && month == 2 && (year % 4 == 0)) return false;
    else if (day > 28 && month == 2 && (year % 4 != 0)) return false;
    else return true;
}

bool correct_date(Date_Last_Visit& date) {
    if (date.year <= 2000 || date.year > 2026) return false;
    if (date.month > 12 || date.month < 1) return false;
    if (!correct_day(date.day, date.month, date.year)) return false;
    else return true;
}

bool correct_address(Address& data) {
    if (data.city.size() < 2 || data.city.size() > 15) return false;
    if (data.district.size() < 2 || data.district.size() > 10) return false;
    if (data.street.size() < 2 || data.street.size() > 15) return false;
    try {
        std::stoi(data.building);
        std::stoi(data.apartment);
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    if (std::stoi(data.building) < 1 || std::stoi(data.building) > 150) return false;
    if (std::stoi(data.apartment) < 1 || std::stoi(data.apartment) > 1000) return false;
    else return true;
}

bool correct_name(Patient& data) {
    if (data.name.size() < 2 || data.name.size() > 10) return false;
    if (data.surname.size() < 2 || data.surname.size() > 10) return false;
    if (data.last_name.size() < 5 || data.last_name.size() > 15) return false;
    else return true;
}
