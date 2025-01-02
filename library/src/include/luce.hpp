#ifndef LUCE_H
#define LUCE_H

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <KinematicBody2D.hpp>
#include <Vector2.hpp>

namespace godot {
    class Luce : public KinematicBody2D {
        GODOT_CLASS(Luce, KinematicBody2D);

        private:
            AnimatedSprite* anim;
            Input* input;
            bool jumped;
            Vector2 velocity;
            bool was_going_left;
            float jump;
            float gravity;
            float speed;

        public:
            Luce();
            ~Luce();
            static void _register_methods();
            void _init();
            void _ready();
            void _physics_process(float delta);
    };
}

#endif