#ifndef DEMON_JUMP_H
#define DEMON_JUMP_H

#include "demon_state.hpp"

class DemonJump : public DemonState {
    public:
        DemonJump();
        ~DemonJump();
        void enter(godot::Demon& demon);
        void exit(godot::Demon& demon);
        DemonState* update(godot::Demon& demon);
};

#endif