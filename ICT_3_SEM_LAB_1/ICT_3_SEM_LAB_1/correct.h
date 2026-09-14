#ifndef CORRECT_H
#define CORRECT_H

#include "doublelinkedlist.h"

bool correct_day(int day, int month, int year);
bool correct_date(Date_Last_Visit& date);
bool correct_address(Address& data);
bool correct_name(Patient& data);

#endif //CORRECT_H