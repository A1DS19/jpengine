#include "engine/engine.hpp"
#include "engine/src/engine.hpp"
#include "game.hpp"

#include <cstdlib>

int main() {
    Game* game = new Game;
    auto& eng = engine::Engine::get_instance();

    eng.set_application(game);

    if (eng.init()) {
        eng.run();
    }

    eng.destroy();

    return EXIT_SUCCESS;
}
