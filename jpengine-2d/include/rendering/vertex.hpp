#pragma once

#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <sol/state.hpp>
namespace jpengine {
struct UV {
    float u_{0.F};
    float v_{0.F};
    float uv_widht_{0.F};
    float uv_height_{0.F};
};

struct Color {
    std::uint8_t r_{255};
    std::uint8_t g_{255};
    std::uint8_t b_{255};
    std::uint8_t a_{255};
};

struct Vertex {
    glm::vec2 position_{0.F};
    UV uvs_{};
    Color color_{.r_ = 255, .g_ = 255, .b_ = 255, .a_ = 255};
    static void create_lua_bind(sol::state& lua);
};

struct ShapeVertex {
    glm::vec2 position_{0.F};
    Color color_{.r_ = 255, .g_ = 255, .b_ = 255, .a_ = 255};
};

} // namespace jpengine
