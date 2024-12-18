#include "demon.hpp"

using namespace godot;

void Demon::_register_methods() {
    // Register _process function here
    register_method("_physics_process", &Demon::_physics_process);
}