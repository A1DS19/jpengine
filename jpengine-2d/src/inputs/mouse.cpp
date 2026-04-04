#include "inputs/mouse.hpp"

#include "inputs/button.hpp"

#include <SDL2/SDL_mouse.h>
#include <glm/ext/vector_float2.hpp>
#include <tuple>

using namespace jpengine;

Mouse::Mouse()
    : mx_{0}, my_{0}, wheel_x_{0}, wheel_y_{0}, moving_{false},
      map_buttons_{{MOUSE_LEFT, Button{}}, {MOUSE_MIDDLE, Button{}}, {MOUSE_RIGHT, Button{}}} {}

Mouse::~Mouse() = default;

void Mouse::update() {
    for (auto& [_, btn] : map_buttons_) {
        btn.reset();
    }

    wheel_x_ = 0;
    wheel_y_ = 0;
    moving_ = false;
}

void Mouse::on_btn_pressed(int btn) {
    if (btn == MOUSE_UNKNOWN) {
        return;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return;
    }

    btn_itr->second.update(true);
}

void Mouse::on_btn_released(int btn) {
    if (btn == MOUSE_UNKNOWN) {
        return;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return;
    }

    btn_itr->second.update(false);
}

bool Mouse::is_btn_pressed(int btn) const {
    if (btn == MOUSE_UNKNOWN) {
        return false;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return false;
    }

    return btn_itr->second.is_pressed_;
}

bool Mouse::is_btn_just_pressed(int btn) const {
    if (btn == MOUSE_UNKNOWN) {
        return false;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return false;
    }

    return btn_itr->second.just_pressed_;
}

bool Mouse::is_btn_just_released(int btn) const {
    if (btn == MOUSE_UNKNOWN) {
        return false;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return false;
    }

    return btn_itr->second.just_released_;
}

const std::tuple<int, int> Mouse::get_mouse_screen_position() {
    SDL_GetMouseState(&mx_, &my_);
    return std::make_tuple(mx_, my_);
}

void Mouse::create_lua_bind(sol::state& lua, Mouse& mouse) {
    lua.set("LEFT_BTN", MOUSE_LEFT);
    lua.set("MIDDLE_BTN", MOUSE_MIDDLE);
    lua.set("RIGHT_BTN", MOUSE_RIGHT);

    lua.new_usertype<Mouse>(
        "Mouse", sol::no_constructor, "just_pressed",
        [&](int btn) { return mouse.is_btn_just_pressed(btn); }, "just_released",
        [&](int btn) { return mouse.is_btn_just_released(btn); }, "pressed",
        [&](int btn) { return mouse.is_btn_pressed(btn); }, "screen_position",
        [&] {
            auto [x, y] = mouse.get_mouse_screen_position();
            return glm::vec2{x, y};
        },
        "wheel_x", [&] { return mouse.get_mouse_wheel_x(); }, "wheel_y",
        [&] { return mouse.get_mouse_wheel_y(); });
}
