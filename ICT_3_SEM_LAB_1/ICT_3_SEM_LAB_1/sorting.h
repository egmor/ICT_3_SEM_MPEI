#ifndef SORTING_H
#define SORTING_H

#include "doublelinkedlist.h"

bool is_date_greater(const Date_Last_Visit& a, const Date_Last_Visit& b);
void sort_by_fio(DoublyLinkedList& list);
void sort_by_birth_year(DoublyLinkedList& list);
void sort_by_address(DoublyLinkedList& list);
void sort_by_illness(DoublyLinkedList& list);
void sort_by_date(DoublyLinkedList& list);

#endif //SORTING_H