#include "engine/src/input/input-manager.hpp"

namespace engine {

void InputManager::set_key_pressed(int key_code, bool pressed) {

    if (key_code < 0 && key_code >= static_cast<int>(keys_.size())) {
        return;
    }

    keys_[key_code] = pressed;
}

bool InputManager::is_key_pressed(int key_code) {
    if (key_code < 0 && key_code >= static_cast<int>(keys_.size())) {
        return false;
    }

    return keys_[key_code];
}

} // namespace engine
