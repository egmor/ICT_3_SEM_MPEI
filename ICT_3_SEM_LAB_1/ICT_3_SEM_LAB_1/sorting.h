#ifndef SORTING_H
#define SORTING_H

#include "correct.h"

void sort_by_fio(std::vector<Medical_Record>& records);
void sort_by_address(std::vector<Medical_Record>& records);
void sort_by_date(std::vector<Medical_Record>& records);
//Сортировка по году рождения и болезни
template <typename CompareFunc>
void sort_by(std::vector<Medical_Record>& records, CompareFunc compare) {
    std::sort(records.begin(), records.end(), compare);
}

#endif //SORTING_H