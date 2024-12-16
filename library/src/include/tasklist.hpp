#ifndef TASKLIST_H
#define TASKLIST_H

#include "task.hpp"

class TaskList {
    public:
        Task* head;
        Task* tail;
        int size;
};

#endif