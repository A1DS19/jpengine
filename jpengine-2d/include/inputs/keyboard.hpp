#pragma once

#include "button.hpp"

#include <sol/sol.hpp>
#include <unordered_map>

namespace jpengine {

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    void update();
    void on_key_pressed(int key);
    void on_key_released(int key);

    bool is_key_pressed(int key) const noexcept;
    bool is_key_just_pressed(int key) const noexcept;
    bool is_key_just_released(int key) const noexcept;
    bool is_any_key_pressed() const noexcept;

    static void create_lua_bind(sol::state& lua, Keyboard& keyboard);

private:
    std::unordered_map<int, Button> map_buttons_;
};

} // namespace jpengine
