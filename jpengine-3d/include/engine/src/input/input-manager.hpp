#pragma once

#include <array>

namespace engine {

class Engine; // forward decl — needed only for the `friend class Engine;` below

class InputManager {
private:
    InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager& operator=(const InputManager&&) = delete;

public:
    void set_key_pressed(int key_code, bool pressed);
    bool is_key_pressed(int key_code);

private:
    friend class Engine;
    std::array<bool, 256> keys_ = {false};
};

} // namespace engine
