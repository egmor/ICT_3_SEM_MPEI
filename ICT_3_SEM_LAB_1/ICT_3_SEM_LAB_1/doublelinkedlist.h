#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <format>
#include <utility>

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
    int day{};
    int month{};
    int year{};
};

struct Medical_Record {
    Patient SNL{};
    Address address{};
    Date_Last_Visit date{};
    int birth_year{};
    std::string illness{};
};

struct Node {
    Medical_Record data;
    Node* prev{ nullptr };
    Node* next{ nullptr };
};

struct DoublyLinkedList {
    Node* head{ nullptr };
    Node* tail{ nullptr };
    int size{ 0 };
};

void push_back(DoublyLinkedList& list, const Medical_Record& record);
void push_front(DoublyLinkedList& list, const Medical_Record& record);
void push_index(DoublyLinkedList& list, int index, const Medical_Record& record);
void pop_front(DoublyLinkedList& list);
void pop_back(DoublyLinkedList& list);
void pop_index(DoublyLinkedList& list, int index);
Node* get_node(DoublyLinkedList& list, int index);
void clear_list(DoublyLinkedList& list);

#endif //DOUBLELINKEDLIST_H