#include "ecs/registry.hpp"

#include "ecs/entity.hpp"
#include "utils/meta-utils.hpp"

#include <sol/forward.hpp>
#include <sol/make_reference.hpp>
#include <sol/object.hpp>
#include <sol/overload.hpp>
#include <sol/raii.hpp>
#include <sol/types.hpp>
#include <sol/variadic_args.hpp>

using namespace jpengine;

Registry::Registry() : registry_{std::make_shared<entt::registry>()} {}

void Registry::create_lua_bind(sol::state& lua, Registry& registry) {
    using namespace entt::literals;

    lua.new_enum<ERegistryType>(
        "RegistryType", {{"LUA", ERegistryType::LUA}, {"JPENGINE", ERegistryType::JPENGINE}});

    lua.new_usertype<entt::runtime_view>(
        "runtime_view", sol::no_constructor, "for_each",
        sol::overload(
            [&registry](const entt::runtime_view& view, const sol::function& callback) {
                if (!callback.valid()) {
                    return;
                }
                for (auto entity : view) {
                    callback(Entity{registry, entity});
                }
            },
            [](const entt::runtime_view& view, Registry& reg, const sol::function& callback) {
                if (!callback.valid()) {
                    return;
                }
                for (auto entity : view) {
                    callback(Entity{reg, entity});
                }
            }),
        "exclude",
        [&registry](entt::runtime_view& view, const sol::variadic_args& va) {
            Registry* pRegistry = &registry;
            auto it = va.begin();

            if (it != va.end() && it->is<Registry>()) {
                pRegistry = &it->as<Registry&>();
                ++it;
            }

            for (; it != va.end(); ++it) {
                sol::object obj = *it;
                if (!obj.is<sol::table>()) continue;

                sol::table type = obj.as<sol::table>();
                if (!type.valid()) continue;

                utils::invoke_meta_function(
                    utils::get_id_type(type), "exclude_component_from_view"_hs, pRegistry, &view);
            }
        });

    lua.new_usertype<Registry>(
        "Registry", sol::call_constructor,
        sol::factories(
            [&registry](sol::this_state state) {
                return sol::make_reference(state, std::ref(registry));
            },
            [](ERegistryType type, sol::this_state state) -> sol::object {
                return type != ERegistryType::LUA ? sol::object{}
                                                  : sol::make_object(state, Registry{});
            }),
        "get_entities",
        [](Registry& reg, const sol::variadic_args& va) {
            entt::runtime_view view{};
            for (const auto& type : va) {
                if (!type.as<sol::table>().valid()) {
                    continue;
                }
                const auto entities = utils::invoke_meta_function(
                    utils::get_id_type(type.as<sol::table>()), "add_component_to_view"_hs, &reg);
                view = entities ? entities.cast<entt::runtime_view>() : view;
            }
            return view;
        },
        "create_entity", [](Registry& reg) { return Entity{reg}; }, "clear",
        [](Registry& reg) { reg.clear_registry(); });
}
