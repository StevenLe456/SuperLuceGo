#include "demon.hpp"

#include <Area2D.hpp>
#include <KinematicCollision2D.hpp>

#include <cmath>
#include <iostream>

using namespace godot;

DemonState::DemonState() {

}

DemonState::~DemonState() {

}

DemonState* DemonState::update(godot::Demon& demon) {
    return NULL;
}

DemonStill::DemonStill() {

}

DemonStill::~DemonStill() {

}

DemonState* DemonStill::update(godot::Demon& demon) {
    demon.set_velocity(godot::Vector2(0, 0));
    demon.animation = "still";
    if (demon.dying) {
        return new DemonDie();
    }
    if (demon.chase) {
        return new DemonChase();
    }
    if (demon.evade) {
        return new DemonEvade();
    }
    return NULL;
}

DemonChase::DemonChase() {

}

DemonChase::~DemonChase() {

}

DemonState* DemonChase::update(Demon& demon) {
    KinematicBody2D* luce = demon.get_parent()->get_parent()->get_node<KinematicBody2D>("Luce");
    float distance = demon.get_position().x - luce->get_position().x;
    if (distance > 0.0) {
        demon.set_velocity(Vector2(-demon.get_speed(), 0));
    }
    else {
        demon.set_velocity(Vector2(demon.get_speed(), 0));
    }
    demon.animation = "move";
    if (demon.dying) {
        return new DemonDie();
    }
    if (!demon.chase && !demon.evade) {
        return new DemonStill();
    }
    if (demon.evade) {
        return new DemonEvade();
    }
    return NULL;
}

DemonEvade::DemonEvade() {

}

DemonEvade::~DemonEvade() {

}

DemonState* DemonEvade::update(Demon& demon) {
    KinematicBody2D* luce = demon.get_parent()->get_parent()->get_node<KinematicBody2D>("Luce");
    float distance = demon.get_position().x - luce->get_position().x;
    if (distance > 0.0) {
        demon.set_velocity(Vector2(demon.get_speed(), 0));
    }
    else {
        demon.set_velocity(Vector2(-demon.get_speed(), 0));
    }
    demon.animation = "move";
    if (demon.dying) {
        return new DemonDie();
    }
    if (!demon.chase && !demon.evade) {
        return new DemonStill();
    }
    if (demon.chase) {
        return new DemonChase();
    }
    return NULL;
}

DemonDie::DemonDie() {

}

DemonDie::~DemonDie() {

}

DemonState* DemonDie::update(Demon& demon) {
    if (demon.get_parent()->get_parent()->get_node<KinematicBody2D>("Luce")->get("rosary_power")) {
        Godot::print("I vanquish demons with the help of the Theotokos!!!");
    }
    else {
        Godot::print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAH");
    }
    demon.queue_free();
    return NULL;
}

void Demon::_register_methods() {
    // Register _process function here
    register_method("_ready", &Demon::_ready);
    register_method("_physics_process", &Demon::_physics_process);
    register_method("_on_hitbox_body_entered", &Demon::_on_hitbox_body_entered);
}

Demon::Demon() {
    state = new DemonStill();
}

Demon::~Demon() {
    delete state;
}

void Demon::_init() {
    speed = 150.0;
    chase = false;
    evade = false;
}

void Demon::_ready() {
    anim = get_node<AnimatedSprite>("AnimatedSprite");
    luce = get_parent()->get_parent()->get_node<Luce>("Luce");
    Area2D* hitbox = get_node<Area2D>("Area2D");
    hitbox->connect("body_entered", this, "_on_hitbox_body_entered");
}

void Demon::_physics_process(float delta) {
    // Might also have to check if y-distance between demon and Luce is zero...
    float distance = std::abs(luce->get_position().x - get_position().x);
    chase = distance <= 500.0 && !luce->get_rosary_power();
    evade = distance <= 500.0 && luce->get_rosary_power();
    DemonState* s = state->update(*this);
    move_and_slide(velocity);
    anim->play(animation);
    if (s != NULL) {
        delete state;
        state = s;
    }
}

void Demon::_on_hitbox_body_entered(Variant v) {
    Node* n = (Node*) v;
    if (n->get_name() == "Luce") {
        dying = true;
    }
}

void Demon::set_velocity(Vector2 v) {
    velocity = v;
}

float Demon::get_speed() {
    return speed;
}