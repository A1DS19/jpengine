#pragma once

#include <entt.hpp>
#include <memory>
#include <sol/sol.hpp>
#include <sol/state.hpp>

namespace jpengine {
enum class ERegistryType { LUA, JPENGINE };

class Registry {
public:
    Registry();
    ~Registry() = default;

    bool is_valid(entt::entity& entity) const noexcept { return registry_->valid(entity); }
    [[nodiscard]] entt::registry& get_registry() const noexcept { return *registry_; }
    entt::entity create_entity() noexcept { return registry_->create(); }
    void clear_registry() noexcept { registry_->clear<entt::registry>(); }

    template <typename TContext>
    TContext add_to_context(TContext context);

    template <typename TContext>
    [[nodiscard]] TContext& get_context();

    template <typename TContext>
    [[nodiscard]] TContext* try_get_context();

    template <typename TContext>
    bool remove_context(TContext context);

    template <typename TContext>
    bool has_context(TContext context);

    static void create_lua_bind(sol::state& lua, Registry& registry);

    template <typename TComponent>
    static void register_meta_component();

private:
    std::shared_ptr<entt::registry> registry_;
    ERegistryType eregistry_type_{ERegistryType::JPENGINE};
};

template <typename TComponent>
entt::runtime_view& add_component_to_view(Registry* pregistry, entt::runtime_view& view);

template <typename TComponent>
void exclude_component_from_view(Registry* pregistry, entt::runtime_view* view);
} // namespace jpengine

#include "../../src/ecs/registry.inl"
