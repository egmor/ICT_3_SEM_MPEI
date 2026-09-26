#include "correct.h"

bool correct_day(Date_Last_Visit date) {
    if (date.day > 31 || date.day < 1) return false;
    else if (date.day > 30 && (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)) return false;
    else if (date.day > 29 && date.month == 2 && (date.year % 4 == 0)) return false;
    else if (date.day > 28 && date.month == 2 && (date.year % 4 != 0 || (date.year % 100 == 0 && date.year % 400 == 0))) return false;
    else return true;
}

bool correct_date(Medical_Record& data) {
    if (data.date.year <= 2000 || data.date.year > 2026) return false;
    if (data.date.month > 12 || data.date.month < 1) return false;
    if (!correct_day(data.date)) return false;
    if (data.date.year - data.birth_year < 18) return false;
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
