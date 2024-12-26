#ifndef DEMON_DIE_H
#define DEMON_DIE_H

#include "demon_state.hpp"

class DemonDie : public DemonState {
    public:
        DemonDie();
        ~DemonDie();
        void enter(godot::Demon& demon);
        void exit(godot::Demon& demon);
        DemonState* update(godot::Demon& demon);
};

#endif