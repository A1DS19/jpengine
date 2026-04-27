#include "engine/src/input/input-manager.hpp"

namespace engine {

void InputManager::set_key_pressed(int key_code, bool pressed) {

    if (key_code < 0 || key_code >= static_cast<int>(keys_.size())) {
        return;
    }

    keys_[static_cast<std::size_t>(key_code)] = pressed;
}

bool InputManager::is_key_pressed(int key_code) {
    if (key_code < 0 || key_code >= static_cast<int>(keys_.size())) {
        return false;
    }

    return keys_[static_cast<std::size_t>(key_code)];
}

void InputManager::set_mouse_pressed(int button, bool pressed) {
    if (button < 0 || button >= static_cast<int>(mouse_keys_.size())) {
        return;
    }

    mouse_keys_[static_cast<std::size_t>(button)] = pressed;
}

bool InputManager::is_mouse_button_pressed(int button) {
    if (button < 0 || button >= static_cast<int>(mouse_keys_.size())) {
        return false;
    }

    return mouse_keys_[static_cast<std::size_t>(button)];
}

} // namespace engine
