#ifndef DEMON_CHASE_H
#define DEMON_CHASE_H

#include "demon_state.hpp"

class DemonChase : public DemonState {
    public:
        DemonChase();
        ~DemonChase();
        void enter(godot::Demon& demon);
        void exit(godot::Demon& demon);
        DemonState* update(godot::Demon& demon);
};

#endif