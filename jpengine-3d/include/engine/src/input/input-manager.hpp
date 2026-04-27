#pragma once

#include <array>
#include <glm/ext/vector_float2.hpp>

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
    void set_mouse_pressed(int button, bool pressed);
    bool is_mouse_button_pressed(int button);
    void set_mouse_position_old(const glm::vec2& pos) { mouse_position_old_ = pos; }
    [[nodiscard]] glm::vec2& get_mouse_position_old() { return mouse_position_old_; }
    void set_mouse_position_current(const glm::vec2& pos) { mouse_position_current_ = pos; }
    [[nodiscard]] glm::vec2& get_mouse_position_current() { return mouse_position_current_; }

private:
    friend class Engine;
    std::array<bool, 256> keys_ = {false};
    std::array<bool, 16> mouse_keys_ = {false};
    glm::vec2 mouse_position_old_ = glm::vec2(0.0F);
    glm::vec2 mouse_position_current_ = glm::vec2(0.0F);
};

} // namespace engine
