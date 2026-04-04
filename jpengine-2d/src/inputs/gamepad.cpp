#include "inputs/gamepad.hpp"

#include "inputs/button.hpp"
#include "inputs/gamepad_buttons.hpp"

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <string_view>

using namespace jpengine;

bool validate_pcontroller(const jpengine::Controller& pcontroller, std::string_view err = "") {
    if (!pcontroller) {
        if (!err.empty())
            std::cerr << err << "\n";
        return false;
    }
    return true;
}

Gamepad::Gamepad() : Gamepad(nullptr) {}

Gamepad::Gamepad(Controller pcontroller)
    : pcontroller_{std::move(pcontroller)},
      map_buttons_{
          {GP_BTN_A, Button{}},         {GP_BTN_B, Button{}},         {GP_BTN_X, Button{}},
          {GP_BTN_Y, Button{}},         {GP_BTN_BACK, Button{}},      {GP_BTN_GUIDE, Button{}},
          {GP_BTN_START, Button{}},     {GP_BTN_LSTICK, Button{}},    {GP_BTN_RSTICK, Button{}},
          {GP_BTN_LSHOULDER, Button{}}, {GP_BTN_RSHOULDER, Button{}}, {GP_BTN_DPAD_UP, Button{}},
          {GP_BTN_DPAD_DOWN, Button{}}, {GP_BTN_DPAD_LEFT, Button{}}, {GP_BTN_DPAD_RIGHT, Button{}},
      },
      map_axis_values_{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}}, instance_id_{-1},
      joystick_hat_value_{HAT_CENTERED}, name_{""} {
    if (pcontroller) {
        SDL_Joystick* pjoystick = SDL_GameControllerGetJoystick(pcontroller.get());
        if (!pjoystick) {
            throw("joystick is invalid");
        }

        instance_id_ = SDL_JoystickInstanceID(pjoystick);
        name_ = std::string{SDL_JoystickName(pjoystick)};
    }
}

Gamepad::~Gamepad() = default;

void Gamepad::update() {
    for (auto& [_, btn] : map_buttons_) {
        btn.reset();
    }
}

void Gamepad::on_btn_pressed(int btn) {

    if (!validate_pcontroller(pcontroller_))
        return;

    if (btn == GP_BTN_UNKNOWN) {
        return;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return;
    }

    btn_itr->second.update(true);
}

void Gamepad::on_btn_released(int btn) {

    if (!validate_pcontroller(pcontroller_))
        return;

    if (btn == GP_BTN_UNKNOWN) {
        return;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return;
    }

    btn_itr->second.update(false);
}

bool Gamepad::is_btn_pressed(int btn) const {

    if (!validate_pcontroller(pcontroller_))
        return false;

    if (btn == GP_BTN_UNKNOWN) {
        return false;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return false;
    }

    return btn_itr->second.is_pressed_;
}

bool Gamepad::is_btn_just_pressed(int btn) const {

    if (!validate_pcontroller(pcontroller_))
        return false;

    if (btn == GP_BTN_UNKNOWN) {
        return false;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return false;
    }

    return btn_itr->second.just_pressed_;
}

bool Gamepad::is_btn_just_released(int btn) const {

    if (!validate_pcontroller(pcontroller_))
        return false;

    if (btn == GP_BTN_UNKNOWN) {
        return false;
    }

    auto btn_itr = map_buttons_.find(btn);
    if (btn_itr == map_buttons_.end()) {
        return false;
    }

    return btn_itr->second.just_released_;
}

Sint16 Gamepad::get_axis_position(Uint8 axis) {
    if (!validate_pcontroller(pcontroller_))
        return -1;

    auto axis_itr = map_axis_values_.find(axis);
    if (axis_itr == map_axis_values_.end()) {
        return 0;
    }

    return axis_itr->second;
}

void Gamepad::set_axis_position_value(Uint8 axis, Sint16 value) {
    if (!validate_pcontroller(pcontroller_))
        return;

    auto axis_itr = map_axis_values_.find(axis);
    if (axis_itr == map_axis_values_.end()) {
        return;
    }

    axis_itr->second = value;
}

bool Gamepad ::is_game_pad_present() const {
    return pcontroller_ != nullptr;
}

void Gamepad::set_controller(jpengine::Controller pcontroller) {
    if (!validate_pcontroller(pcontroller, "failed to set controller"))
        return;

    pcontroller_ = std::move(pcontroller);

    SDL_Joystick* pjoystick = SDL_GameControllerGetJoystick(pcontroller_.get());
    if (!pjoystick) {
        throw("joystick is invalid");
    }

    instance_id_ = SDL_JoystickInstanceID(pjoystick);
    name_ = std::string{SDL_JoystickName(pjoystick)};

    std::cout << "added controller succesfully\n";
}

void Gamepad::remove_controller() {
    if (!validate_pcontroller(pcontroller_, "controller already removed"))
        return;
    update();
    pcontroller_.reset();
    instance_id_ = -1;
    name_ = "";
    std::cout << "removed controller successfully\n";
}

void ControllerDestroyer::operator()(SDL_GameController* pcontroller) const {
    SDL_GameControllerClose(pcontroller);
    std::cout << "removed controller from sdl\n";
}

void Gamepad::create_lua_bind(sol::state& lua, Gamepad& gamepad) {
    lua.set("GP_BTN_A", GP_BTN_A);
    lua.set("GP_BTN_B", GP_BTN_B);
    lua.set("GP_BTN_X", GP_BTN_X);
    lua.set("GP_BTN_Y", GP_BTN_Y);

    lua.set("GP_BTN_BACK", GP_BTN_BACK);
    lua.set("GP_BTN_GUIDE", GP_BTN_GUIDE);
    lua.set("GP_BTN_START", GP_BTN_START);

    lua.set("GP_LSTICK", GP_BTN_LSTICK);
    lua.set("GP_RSTICK", GP_BTN_RSTICK);
    lua.set("GP_LSHOULDER", GP_BTN_LSHOULDER);
    lua.set("GP_RSHOULDER", GP_BTN_RSHOULDER);

    lua.set("DPAD_UP", GP_BTN_DPAD_UP);
    lua.set("DPAD_DOWN", GP_BTN_DPAD_DOWN);
    lua.set("DPAD_LEFT", GP_BTN_DPAD_LEFT);
    lua.set("DPAD_RIGHT", GP_BTN_DPAD_RIGHT);

    lua.set("AXIS_X1", 0);
    lua.set("AXIS_Y1", 1);
    lua.set("AXIS_X2", 2);
    lua.set("AXIS_Y2", 3);

    // Bottom triggers
    lua.set("AXIS_Z1", 4);
    lua.set("AXIS_Z2", 5);

    lua.new_usertype<Gamepad>(
        "Gamepad", sol::no_constructor, "just_pressed",
        [&](int btn) { return gamepad.is_btn_just_pressed(btn); }, "just_released",
        [&](int btn) { return gamepad.is_btn_just_released(btn); }, "pressed",
        [&](int btn) { return gamepad.is_btn_pressed(btn); }, "get_axis_position",
        [&](Uint8 axis) { return gamepad.get_axis_position(axis); }, "get_hat_value",
        [&]() { return gamepad.get_joystick_hat_value(); }, "is_gamepad_present",
        [&]() { return gamepad.is_game_pad_present(); });
}
