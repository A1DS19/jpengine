#include "game.hpp"

#include <cstdlib>
#include <iostream>
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

jpengine::Game game{};

void main_loop() {
    game.run();
}

auto main() -> int {
    if (!game.initialize()) {
        std::cerr << "failed to initialize game\n";
        return EXIT_FAILURE;
    }

    std::cout << "starting game\n";

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (true) {
        main_loop();
    }
#endif

    return EXIT_SUCCESS;
}
