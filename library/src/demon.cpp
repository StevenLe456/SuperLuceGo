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
    if (demon.chase) {
        return new DemonChase();
    }
    return NULL;
}

DemonChase::DemonChase() {

}

DemonChase::~DemonChase() {

}

DemonState* DemonChase::update(Demon& Demon) {
    return NULL;
}

void Demon::_register_methods() {
    // Register _process function here
    register_method("_ready", &Demon::_ready);
    register_method("_physics_process", &Demon::_physics_process);
    register_method("_body_entered", &Demon::_body_entered);
    register_method("_body_exited", &Demon::_body_exited);
}

Demon::Demon() {
    chase = false;
    state = new DemonStill();
}

Demon::~Demon() {
    delete state;
}

void Demon::_init() {

}

void Demon::_ready() {
    Area2D* box = get_node<Area2D>("Area2D");
    box->connect("body_entered", this, "_body_entered");
    box->connect("body_exited", this, "_body_exited");
}

void Demon::_physics_process(float delta) {
    DemonState* s = state->update(*this);
    if (s != NULL) {
        delete state;
        state = s;
    }
}

void Demon::_body_entered(Variant body) {
    Node* n = (Node*) body;
    if (n->get_name() == "Luce") {
        chase = true;
    }
}

void Demon::_body_exited(Variant body) {
    Node* n = (Node*) body;
    if (n->get_name() == "Luce") {
        chase = false;
    }
}

void Demon::set_velocity(Vector2 v) {
    velocity = v;
}