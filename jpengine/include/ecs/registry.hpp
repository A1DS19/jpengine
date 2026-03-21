#pragma once

#include <entt.hpp>
#include <memory>
#include <sol/sol.hpp>
#include <sol/state.hpp>

namespace jpengine {
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

private:
    std::shared_ptr<entt::registry> registry_;
};
} // namespace jpengine

#include "../../src/ecs/registry.inl"
