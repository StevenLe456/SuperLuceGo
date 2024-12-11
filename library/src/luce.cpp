#include "AnimatedSprite.hpp"

#include "luce.hpp"

using namespace godot;

void Luce::_register_methods() {
    // Register _process function here
    register_method("_physics_process", &Luce::_physics_process);

    // Register properties here
    register_property<Luce, float>("jump", &Luce::jump, 300.0);
    register_property<Luce, float>("gravity", &Luce::gravity, 200.0);
    register_property<Luce, float>("speed", &Luce::speed, 100.0);
}

Luce::Luce() {
    input = Input::get_singleton();
}

Luce::~Luce() {
    // Clean up class here
}

void Luce::_init() {
    jumped = false;
    velocity = Vector2(0, 0);
    jump = 300.0;
    gravity = 200.0;
    speed = 100.0;
    was_going_left = false;
}

void Luce::_physics_process(float delta) {
    // Vertical motion logic
    if (!is_on_floor() && jumped) {
        jumped = false;
    }
    else if (is_on_floor() && input->is_action_just_pressed("jump")) {
        jumped = true;
        velocity.y = 0;
        velocity.y -= jump;
    }
    else if (!is_on_floor()) {
        velocity.y += gravity * delta;
    }
    else {
        // Empty
    }
    // Horizontal motion logic
    if (input->is_action_pressed("left")) {
        velocity.x = -speed;
    }
    else if (input->is_action_pressed("right")) {
        velocity.x = speed;
    }
    else {
        velocity.x = 0;
    }
    velocity = move_and_slide(velocity, Vector2::UP);
    // Aimation logic
    if (is_on_floor()) {
        if (velocity.x > 0) {
            get_node<AnimatedSprite>("AnimatedSprite")->set_flip_h(false);
            get_node<AnimatedSprite>("AnimatedSprite")->play("walk");
            was_going_left = false;
        }
        else if (velocity.x < 0) {
            get_node<AnimatedSprite>("AnimatedSprite")->set_flip_h(true);
            get_node<AnimatedSprite>("AnimatedSprite")->play("walk");
            was_going_left = true;
        }
        else {
            get_node<AnimatedSprite>("AnimatedSprite")->play("stand");
        }
    }
    else if (!is_on_floor()) {
        if ((velocity.y != 0 && velocity.x < 0) || (velocity.y != 0 && velocity.x == 0 && was_going_left)) {
            get_node<AnimatedSprite>("AnimatedSprite")->set_flip_h(true);
            get_node<AnimatedSprite>("AnimatedSprite")->play("jump");
        }
        else if (velocity.y != 0 && velocity.x >= 0) {
            get_node<AnimatedSprite>("AnimatedSprite")->set_flip_h(false);
            get_node<AnimatedSprite>("AnimatedSprite")->play("jump");
        }
        else {
            // Empty
        }
    }
    else {
        // Empty
    }
}