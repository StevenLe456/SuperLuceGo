#ifndef DEMON_EVADE_H
#define DEMON_EVADE_H

#include "demon_state.hpp"

class DemonEvade : public DemonState {
    public:
        DemonEvade();
        ~DemonEvade();
        void enter(godot::Demon& demon);
        void exit(godot::Demon& demon);
        DemonState* update(godot::Demon& demon);
};

#endif