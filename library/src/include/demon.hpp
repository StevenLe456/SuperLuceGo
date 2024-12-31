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
            bool chase;
            bool evade;

            Demon();
            ~Demon();
            static void _register_methods();
            void _init();
            void _ready();
            void _physics_process(float delta);
            void _body_entered(Variant body);
            void _body_exited(Variant body);
            void set_velocity(Vector2 v);
    };

    class DemonState {
        public:
            DemonState();
            virtual ~DemonState();
            virtual DemonState* update(godot::Demon& demon);
    };

    class DemonStill : public DemonState {
        public:
            DemonStill();
            ~DemonStill();
            DemonState* update(godot::Demon& demon);
    };

    class DemonChase : public DemonState {
        public:
            DemonChase();
            ~DemonChase();
            DemonState* update(godot::Demon& demon);
    };
}

#endif