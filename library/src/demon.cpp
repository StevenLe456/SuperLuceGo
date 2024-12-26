#include "demon.hpp"

#include "Area2D.hpp"

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
    if (demon.get_node<godot::Area2D>("Area2D")->get_overlapping_bodies().size() > 0) {
        std::cout << demon.get_node<godot::Area2D>("Area2D")->get_overlapping_bodies().size() << std::endl;
    }
    return NULL;
}

void Demon::_register_methods() {
    // Register _process function here
    register_method("_physics_process", &Demon::_physics_process);
}

Demon::Demon() {
    state = new DemonStill();
}

Demon::~Demon() {
    delete state;
}

void Demon::_init() {

}

void Demon::_physics_process(float delta) {
    DemonState* s = state->update(*this);
    if (s != NULL) {
        delete state;
        state = s;
    }
}

void Demon::set_velocity(Vector2 v) {
    velocity = v;
}