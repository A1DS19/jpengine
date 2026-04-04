#pragma once

#include "button.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_stdinc.h>
#include <memory>
#include <sol/sol.hpp>
#include <sol/state.hpp>
#include <string>
#include <unordered_map>

namespace jpengine {

struct ControllerDestroyer {
    void operator()(SDL_GameController* pcontroller) const;
};

using Controller = std::shared_ptr<SDL_GameController>;

inline Controller make_shared_controller(SDL_GameController* pcontroller) {
    return std::shared_ptr<SDL_GameController>(pcontroller, ControllerDestroyer{});
}

class Gamepad {

public:
    Gamepad();
    Gamepad(Controller pcontroller);
    ~Gamepad();

    void update();

    void on_btn_pressed(int btn);
    void on_btn_released(int btn);

    bool is_btn_pressed(int btn) const;
    bool is_btn_just_pressed(int btn) const;
    bool is_btn_just_released(int btn) const;

    Sint16 get_axis_position(Uint8 axis);
    void set_axis_position_value(Uint8 axis, Sint16 value);

    bool is_game_pad_present() const;
    void set_controller(Controller pcontroller);
    void remove_controller();

    void set_joystick_hat_value(Uint8 value) noexcept { joystick_hat_value_ = value; }
    Uint8 get_joystick_hat_value() const noexcept { return joystick_hat_value_; }

    std::string& get_name() { return name_; }

    static void create_lua_bind(sol::state& lua, Gamepad& gamepad);

private:
    Controller pcontroller_;
    std::unordered_map<int, Button> map_buttons_;
    std::unordered_map<Uint8, Sint16> map_axis_values_;
    SDL_JoystickID instance_id_;
    Uint8 joystick_hat_value_;
    std::string name_;
};

} // namespace jpengine
