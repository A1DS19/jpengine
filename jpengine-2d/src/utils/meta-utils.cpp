#include "utils/meta-utils.hpp"

#include "ecs/component.hpp"

#include <cassert>
#include <iostream>
#include <sol/forward.hpp>

[[nodiscard]] entt::id_type jpengine::utils::get_id_type(const sol::table& comp) {
    if (!comp.valid()) {
        std::cerr << "failed to get type id component has not been exposed to lua\n";
        assert(comp.valid() && "failed to get type id component has not been exposed to lua\n");
        return entt::id_type(-1);
    }

    // When comp is the type table, type_id is a property getter (callable).
    // When comp is a userdata instance, __index returns the integer value directly.
    const auto type_id_field = comp["type_id"];
    if (const auto func = type_id_field.get<sol::function>(); func.valid()) {
        return func().get<entt::id_type>();
    }

    return type_id_field.get<entt::id_type>();
}
