#ifndef DEMON_STATE_H
#define DEMON_STATE_H

#include "demon.hpp"

class DemonState {
    public:
        virtual ~DemonState();
        virtual void update(godot::Demon& demon);
};

#endif