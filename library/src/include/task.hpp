#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
    public:
        int id;
        std::string description;
        Task* prev;
        Task* next;
};

#endif