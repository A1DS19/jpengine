#include "rendering/vertex.hpp"
using namespace jpengine;

void Vertex::create_lua_bind(sol::state& lua) {
    lua.new_usertype<UV>(
        "UV", sol::call_constructor,
        sol::factories([] { return UV{}; },
                       [](float u, float v, float uv_w, float uv_h) {
                           return UV{.u_ = u, .v_ = v, .uv_widht_ = uv_w, .uv_height_ = uv_h};
                       }),
        "u", &UV::u_, "v", &UV::v_, "uv_height", &UV::uv_height_, "uv_widht", &UV::uv_widht_);

    lua.new_usertype<Color>(
        "Color", sol::call_constructor,
        sol::factories([](std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
            return Color{.r_ = r, .g_ = g, .b_ = b, .a_ = a};
        }),
        "r", &Color::r_, "g", &Color::g_, "b", &Color::b_, "a", &Color::a_);

    lua.set("J2D_WHITE", Color{255, 255, 255, 255});
    lua.set("J2D_RED", Color{255, 0, 0, 255});
    lua.set("J2D_GREEN", Color{0, 255, 0, 255});
    lua.set("J2D_BLUE", Color{0, 0, 255, 255});
    lua.set("J2D_BLACK", Color{0, 0, 0, 255});
    lua.set("J2D_YELLOW", Color{255, 255, 0, 255});
    lua.set("J2D_MAGENTA", Color{255, 0, 255, 255});
}
