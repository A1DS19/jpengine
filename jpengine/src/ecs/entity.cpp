#include "ecs/entity.hpp"

#include "ecs/registry.hpp"

#include <cstdint>
#include <sol/raii.hpp>
#include <sol/types.hpp>

using namespace jpengine;

void Entity::create_lua_bind(sol::state& lua, Registry& registry) {
    using namespace entt::literals;

    lua.new_usertype<Entity>(
        "Entity", sol::call_construction,
        sol::factories([](Registry& reg) { return Entity{reg}; },
                       [&registry]() { return Entity{registry}; },
                       [&registry](std::uint32_t id) {
                           return Entity{registry, static_cast<entt::entity>(id)};
                       }),
        "add_component",
        [](Entity& entity, const sol::table& comp, sol::this_state state) -> sol::object {
            if (!comp.valid()) {
                return sol::lua_nil_t{};
            }
        });
}
