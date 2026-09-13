#include "doublelinkedlist.h"

void push_back(DoublyLinkedList& list, const Medical_Record& record) {
    Node* newNode = new Node{ record, list.tail, nullptr };

    if (list.tail != nullptr) list.tail->next = newNode;
    else list.head = newNode;

    list.tail = newNode;
    list.size++;
}

void push_front(DoublyLinkedList& list, const Medical_Record& record) {
    Node* newNode = new Node{ record, nullptr, list.head };

    if (list.head != nullptr) list.head->prev = newNode;
    else list.tail = newNode;

    list.head = newNode;
    list.size++;
}

void push_index(DoublyLinkedList& list, int index, const Medical_Record& record) {
    if (index <= 0) {
        push_front(list, record);
        return;
    }

    if (index >= list.size) {
        push_back(list, record);
        return;
    }

    Node* current{ list.head };
    for (int i{ 0 }; i < index; ++i) current = current->next;

    Node* newNode = new Node{ record, current->prev, current };
    current->prev->next = newNode;
    current->prev = newNode;

    list.size++;
}

void pop_front(DoublyLinkedList& list) {
    if (!list.head) return;

    Node* temp{ list.head };
    list.head = list.head->next;

    if (list.head != nullptr) list.head->prev = nullptr;
    else list.tail = nullptr;

    delete temp;
    list.size--;
}

void pop_back(DoublyLinkedList& list) {
    if (!list.tail) return;

    Node* temp{ list.tail };
    list.tail = list.tail->prev;

    if (list.tail != nullptr) list.tail->next = nullptr;
    else list.head = nullptr;

    delete temp;
    list.size--;
}

void pop_index(DoublyLinkedList& list, int index) {
    if (index < 0 || index >= list.size || !list.head) return;

    if (index == 0) {
        pop_front(list);
        return;
    }

    if (index == list.size - 1) {
        pop_back(list);
        return;
    }

    Node* current{ list.head };

    for (int i{ 0 }; i < index; ++i) {
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    delete current;
    list.size--;
}

Node* get_node(DoublyLinkedList& list, int index) {
    if (index < 0 || index >= list.size) return nullptr;

    Node* current{ list.head };

    for (int i{ 0 }; i < index; ++i) {
        current = current->next;
    }

    return current;
}

void clear_list(DoublyLinkedList& list) {
    while (list.head != nullptr) {
        pop_front(list);
    }
}