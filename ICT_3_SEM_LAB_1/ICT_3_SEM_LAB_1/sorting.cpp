#include "sorting.h"

bool is_date_greater(const Date_Last_Visit& a, const Date_Last_Visit& b) {
    if (a.year != b.year) return a.year > b.year;
    if (a.month != b.month) return a.month > b.month;
    return a.day > b.day;
}

void sort_by_fio(DoublyLinkedList& list) {
    if (!list.head) return;
    bool swapped{};
    do {
        swapped = false;
        Node* current{ list.head };
        while (current->next != nullptr) {
            bool need_swap{ false };
            if (current->data.SNL.surname > current->next->data.SNL.surname) {
                need_swap = true;
            }
            else if (current->data.SNL.surname == current->next->data.SNL.surname) {
                if (current->data.SNL.name > current->next->data.SNL.name) {
                    need_swap = true;
                }
                else if (current->data.SNL.name == current->next->data.SNL.name) {
                    if (current->data.SNL.last_name > current->next->data.SNL.last_name) {
                        need_swap = true;
                    }
                }
            }

            if (need_swap) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_by_birth_year(DoublyLinkedList& list) {
    if (!list.head) return;
    bool swapped{};
    do {
        swapped = false;
        Node* current{ list.head };
        while (current->next != nullptr) {
            if (current->data.birth_year > current->next->data.birth_year) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_by_address(DoublyLinkedList& list) {
    if (!list.head) return;
    bool swapped{};
    do {
        swapped = false;
        Node* current{ list.head };
        while (current->next != nullptr) {
            bool need_swap{ false };
            if (current->data.address.city > current->next->data.address.city) {
                need_swap = true;
            }
            else if (current->data.address.city == current->next->data.address.city) {
                if (current->data.address.street > current->next->data.address.street) {
                    need_swap = true;
                }
                else if (current->data.address.street == current->next->data.address.street) {
                    if (current->data.address.building > current->next->data.address.building) {
                        need_swap = true;
                    }
                }
            }

            if (need_swap) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_by_illness(DoublyLinkedList& list) {
    if (!list.head) return;
    bool swapped{};
    do {
        swapped = false;
        Node* current{ list.head };
        while (current->next != nullptr) {
            if (current->data.illness > current->next->data.illness) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_by_date(DoublyLinkedList& list) {
    if (!list.head) return;
    bool swapped{};
    do {
        swapped = false;
        Node* current{ list.head };
        while (current->next != nullptr) {
            if (is_date_greater(current->data.date, current->next->data.date)) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}