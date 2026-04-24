#include "game.hpp"

#include "test-obj.hpp"

bool Game::init() {
    scene_.create_object<TestObject>("test-object");
    return true;
}

void Game::update(float deltatime) {
    scene_.update(deltatime);
}

void Game::destroy() {}
