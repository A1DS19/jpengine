#pragma once

#include "engine/engine.hpp"

class Game : public engine::Application {
public:
    bool init() override;
    void update(float deltatime = 0.0F) override;
    void destroy() override;
};
