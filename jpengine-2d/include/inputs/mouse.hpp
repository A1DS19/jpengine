#pragma once

#include "button.hpp"

#include <sol/sol.hpp>
#include <sol/state.hpp>
#include <tuple>
#include <unordered_map>

namespace jpengine {
constexpr int MOUSE_UNKNOWN = -1;
constexpr int MOUSE_LEFT = 1;
constexpr int MOUSE_MIDDLE = 2;
constexpr int MOUSE_RIGHT = 3;

class Mouse {

public:
    Mouse();
    ~Mouse();

    void update();

    void on_btn_pressed(int btn);
    void on_btn_released(int btn);

    bool is_btn_pressed(int btn) const;
    bool is_btn_just_pressed(int btn) const;
    bool is_btn_just_released(int btn) const;

    const std::tuple<int, int> get_mouse_screen_position();

    void set_mouse_wheel_values(int wheel_x, int wheel_y) {
        wheel_x_ = wheel_x;
        wheel_y_ = wheel_y;
    }
    void set_mouse_moving(bool moving) { moving_ = moving; }

    int get_mouse_wheel_x() const noexcept { return wheel_x_; }
    int get_mouse_wheel_y() const noexcept { return wheel_y_; }

    bool is_mouse_moving() const noexcept { return moving_; }

    static void create_lua_bind(sol::state& lua, Mouse& mouse);

private:
    int mx_;
    int my_;
    int wheel_x_;
    int wheel_y_;
    bool moving_;
    std::unordered_map<int, Button> map_buttons_;
};

} // namespace jpengine
