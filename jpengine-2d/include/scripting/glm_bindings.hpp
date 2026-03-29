#pragma once
#include <sol/sol.hpp>

namespace jpengine {
struct GlmBinder {
    static void create_lua_bind(sol::state& lua);
};
} // namespace jpengine
