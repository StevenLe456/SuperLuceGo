#ifndef DEMON_H
#define DEMON_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Vector2.hpp>

namespace godot {
    class DemonState;
    
    class Demon : public KinematicBody2D {
        GODOT_CLASS(Demon, KinematicBody2D);

        private:
            Vector2 velocity;
            float gravity;
            float speed;
            DemonState* state;

        public:
            Demon();
            ~Demon();
            static void _register_methods();
            void _init();
            void _physics_process(float delta);
            void set_velocity(Vector2 v);
    };

    class DemonState {
        public:
            DemonState();
            ~DemonState();
            DemonState* update(godot::Demon& demon);
    };

    class DemonStill : public DemonState {
        public:
            DemonStill();
            ~DemonStill();
            DemonState* update(godot::Demon& demon);
    };
}

#endif