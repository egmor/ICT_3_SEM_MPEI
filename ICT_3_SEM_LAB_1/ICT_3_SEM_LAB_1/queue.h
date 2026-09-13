#ifndef QUEUE_H
#define QUEUE_H

#include "doublelinkedlist.h"

struct QueueNode {
    Medical_Record data;
    QueueNode* next{ nullptr };
};

struct Queue {
    QueueNode* head{ nullptr };
    QueueNode* tail{ nullptr };
    int size{ 0 };
};

void push_queue(Queue& q, const Medical_Record& record);
bool pop_queue(Queue& q, Medical_Record& outRecord);
void clear_queue(Queue& q);

#endif