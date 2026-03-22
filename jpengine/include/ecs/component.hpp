#pragma once

#include "rendering/vertex.hpp"

#include <SDL2/SDL_timer.h>
#include <entt.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>
#include <sol/state.hpp>
#include <string>

namespace jpengine {
struct Identification {
    std::string tag_{"game_object"};
    std::string group_;
    std::uint32_t entity_id_{entt::null};
};

struct TransformComponent {
    glm::vec2 position_{0.F};
    glm::vec2 scale_{1.F};
    float rotation_{0.F};
};

struct SpriteComponent {
    std::string string_;
    float width_{16.F};
    float height_{16.F};
    UV uvs_{};
    int layer_{0};
    int start_x_{0};
    int start_y_{0};
    bool hidden_{false};
    Color color_{255, 255, 255, 255};

    void generate_uvs(int texture_w, int texture_h) noexcept {
        uvs_.uv_widht_ = width_ / static_cast<float>(texture_w);
        uvs_.uv_height_ = height_ / static_cast<float>(texture_h);

        uvs_.u_ = static_cast<float>(start_x_) * uvs_.uv_widht_;
        uvs_.v_ = static_cast<float>(start_y_) * uvs_.uv_height_;
    }

    void inspect_uvs() noexcept {
        uvs_.u_ = static_cast<float>(start_x_) * uvs_.uv_widht_;
        uvs_.v_ = static_cast<float>(start_y_) * uvs_.uv_height_;
    }

    void inspect_y() noexcept { uvs_.v_ = static_cast<float>(start_y_) * uvs_.uv_height_; }

    void inspect_x() noexcept { uvs_.u_ = static_cast<float>(start_x_) * uvs_.uv_widht_; }
};

struct AnimationComponent {
    int new_frames_{0};
    int current_frame_{0};
    int frame_offset_{0};
    int frame_rate_{0};
    int start_time_{static_cast<int>(SDL_GetTicks())};
    bool vertical_{false};
    bool looped_{false};
    bool stop_{false};

    void reset() noexcept {
        current_frame_ = 0;
        start_time_ = static_cast<int>(SDL_GetTicks());
    }
};

struct BoxColider {
    int width_{16};
    int height_{16};
    glm::vec2 offset_{0.F};
    bool collider_{true};
};

struct CircleCollider {
    float radius_{16.F};
    glm::vec2 offset_{0.F};
    bool trigger_{false};
    bool collider_{false};
};

struct RigidBodyComponent {
    glm::vec2 velocity_{0.F};
    float max_velocity_{100.F};
};

struct ComponentBinder {
    static void create_lua_bind(sol::state& lua);
};

} // namespace jpengine
