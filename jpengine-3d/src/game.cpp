#include "game.hpp"

#include "GLFW/glfw3.h"
#include "engine/src/engine.hpp"

#include <iostream>

bool Game::init() {
    return true;
}

void Game::update(float) {
    auto& input = engine::Engine::get_instance().get_input_manager();
    if (input.is_key_pressed(GLFW_KEY_A)) {
        std::cout << "key a pressed\n";
    }
}

void Game::destroy() {}
