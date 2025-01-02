#include "luce.hpp"

using namespace godot;

void Luce::_register_methods() {
    // Register _process function here
    register_method("_ready", &Luce::_ready);
    register_method("_physics_process", &Luce::_physics_process);
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
    jump = 500.0;
    gravity = 600.0;
    speed = 200.0;
    was_going_left = false;
}

void Luce::_ready() {
    anim = get_node<AnimatedSprite>("AnimatedSprite");
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
            anim->set_flip_h(false);
            anim->play("walk");
            was_going_left = false;
        }
        else if (velocity.x < 0) {
            anim->set_flip_h(true);
            anim->play("walk");
            was_going_left = true;
        }
        else {
            anim->play("stand");
        }
    }
    else if (!is_on_floor()) {
        if ((velocity.y != 0 && velocity.x < 0) || (velocity.y != 0 && velocity.x == 0 && was_going_left)) {
            anim->set_flip_h(true);
            anim->play("jump");
        }
        else if (velocity.y != 0 && velocity.x >= 0) {
            anim->set_flip_h(false);
            anim->play("jump");
        }
        else {
            // Empty
        }
    }
    else {
        // Empty
    }
}