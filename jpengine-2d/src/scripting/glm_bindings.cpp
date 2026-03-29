#include "scripting/glm_bindings.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

using namespace jpengine;

static void create_vec2_bind(sol::state& lua) {
    auto multiply = sol::overload([](const glm::vec2& a, const glm::vec2& b) { return a * b; },
                                  [](const glm::vec2& a, float v) { return a * v; },
                                  [](float v, const glm::vec2& a) { return a * v; });

    auto divide = sol::overload([](const glm::vec2& a, const glm::vec2& b) { return a / b; },
                                [](const glm::vec2& a, float v) { return a / v; });

    auto add = sol::overload([](const glm::vec2& a, const glm::vec2& b) { return a + b; },
                             [](const glm::vec2& a, float v) { return a + v; },
                             [](float v, const glm::vec2& a) { return a + v; });

    auto sub = sol::overload([](const glm::vec2& a, const glm::vec2& b) { return a - b; },
                             [](const glm::vec2& a, float v) { return a - v; });

    lua.new_usertype<glm::vec2>(
        "vec2", sol::call_constructor,
        sol::constructors<glm::vec2(float), glm::vec2(float, float)>(), "x", &glm::vec2::x, "y",
        &glm::vec2::y, sol::meta_function::multiplication, multiply, sol::meta_function::division,
        divide, sol::meta_function::addition, add, sol::meta_function::subtraction, sub, "length",
        [](const glm::vec2& v) { return glm::length(v); }, "length_sq",
        [](const glm::vec2& v) { return glm::length2(v); }, "normalize",
        [](const glm::vec2& v) { return glm::normalize(v); });
}

static void create_vec3_bind(sol::state& lua) {
    auto multiply = sol::overload([](const glm::vec3& a, const glm::vec3& b) { return a * b; },
                                  [](const glm::vec3& a, float v) { return a * v; },
                                  [](float v, const glm::vec3& a) { return a * v; });

    auto divide = sol::overload([](const glm::vec3& a, const glm::vec3& b) { return a / b; },
                                [](const glm::vec3& a, float v) { return a / v; });

    auto add = sol::overload([](const glm::vec3& a, const glm::vec3& b) { return a + b; },
                             [](const glm::vec3& a, float v) { return a + v; });

    auto sub = sol::overload([](const glm::vec3& a, const glm::vec3& b) { return a - b; },
                             [](const glm::vec3& a, float v) { return a - v; });

    lua.new_usertype<glm::vec3>(
        "vec3", sol::call_constructor,
        sol::constructors<glm::vec3(float), glm::vec3(float, float, float)>(), "x", &glm::vec3::x,
        "y", &glm::vec3::y, "z", &glm::vec3::z, sol::meta_function::multiplication, multiply,
        sol::meta_function::division, divide, sol::meta_function::addition, add,
        sol::meta_function::subtraction, sub, "length",
        [](const glm::vec3& v) { return glm::length(v); }, "length_sq",
        [](const glm::vec3& v) { return glm::length2(v); }, "normalize",
        [](const glm::vec3& v) { return glm::normalize(v); });
}

void GlmBinder::create_lua_bind(sol::state& lua) {
    create_vec2_bind(lua);
    create_vec3_bind(lua);
}
