#include "ecs/registry.hpp"

using namespace jpengine;

Registry::Registry() : registry_{std::make_shared<entt::registry>()} {}

void Registry::create_lua_bind(sol::state& /*lua*/, Registry& /*registry*/) {
    // todo: add registry lua bindings.
}
