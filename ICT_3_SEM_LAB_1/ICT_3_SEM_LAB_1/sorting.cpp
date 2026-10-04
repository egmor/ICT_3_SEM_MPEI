#include "sorting.h"

void sort_by_fio(std::vector<Medical_Record>& records) {
    std::sort(records.begin(), records.end(), [](const Medical_Record& a, const Medical_Record& b) {
        if (a.SNL.surname == b.SNL.surname) {
            if (a.SNL.name == b.SNL.name) return a.SNL.last_name < b.SNL.last_name;
            return a.SNL.name < b.SNL.name;
        }
        return a.SNL.surname < b.SNL.surname;
    });
}

void sort_by_address(std::vector<Medical_Record>& records) {
    std::sort(records.begin(), records.end(), [](const Medical_Record& a, const Medical_Record& b) {
        if (a.address.city == b.address.city) {
            if (a.address.district == b.address.district) {
                if (a.address.street == b.address.street) {
                    if (a.address.building == b.address.building) return a.address.apartment < b.address.apartment;
                    return a.address.building < b.address.building;
                }
                return a.address.street < b.address.street;
            }
            return a.address.district < b.address.district;
        }
        return a.address.city < b.address.city;
    });
}

void sort_by_date(std::vector<Medical_Record>& records) {
    std::sort(records.begin(), records.end(), [](const Medical_Record& a, const Medical_Record& b) {
        if (a.date.year == b.date.year) {
            if (a.date.month == b.date.month) return a.date.day < b.date.day;
            return a.date.month < b.date.month;
        }
        return a.date.year < b.date.year;
    });
}