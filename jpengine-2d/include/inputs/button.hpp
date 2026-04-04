#pragma once

namespace jpengine {

struct Button {
    bool is_pressed_{false};
    bool just_pressed_{false};
    bool just_released_{false};

    void update(bool pressed) noexcept {
        just_pressed_ = !is_pressed_ && pressed;
        just_released_ = is_pressed_ && !pressed;

        is_pressed_ = pressed;
    }

    void reset() noexcept {
        just_pressed_ = false;
        just_released_ = false;
    }
};

} // namespace jpengine
