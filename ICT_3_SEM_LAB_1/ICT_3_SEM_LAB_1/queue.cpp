#include "queue.h"

void push_queue(Queue& q, const Medical_Record& record) {
    QueueNode* newNode = new QueueNode{ record, nullptr };
    if (q.tail != nullptr) q.tail->next = newNode;
    else q.head = newNode;

    q.tail = newNode;
    q.size++;
}

bool pop_queue(Queue& q, Medical_Record& outRecord) {
    if (q.head == nullptr) return false;

    QueueNode* temp {q.head};
    outRecord = temp->data;

    q.head = q.head->next;
    if (q.head == nullptr) q.tail = nullptr;

    delete temp;
    q.size--;
    return true;
}

void clear_queue(Queue& q) {
    Medical_Record temp;
    while (pop_queue(q, temp));
}