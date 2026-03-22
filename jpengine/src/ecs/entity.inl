#include "ecs/entity.hpp"

#include <utility>

using namespace jpengine;

template <typename TComponent, typename... Args>
TComponent& Entity::add_component(Args&&... args) {
    auto& registry = registry_.get_registry();
    return registry.emplace<TComponent>(entity_, std::forward<Args>(args)...);
}

template <typename TComponent, typename... Args>
TComponent& Entity::replace_component(Args&&... args) {
    auto& registry = registry_.get_registry();

    if (registry.all_of<TComponent>(entity_)) {
        return registry.replace<TComponent>(entity_, std::forward<Args>(args)...);
    }

    return registry.emplace<TComponent>(entity_, std::forward<Args>(args)...);
}

template <typename TComponent>
TComponent& Entity::get_component() {
    auto& registry = registry_.get_registry();
    return registry.get<TComponent>(entity_);
}

template <typename TComponent>
TComponent* Entity::try_get_component() {
    auto& registry = registry_.get_registry();
    return registry.try_get<TComponent>(entity_);
}

template <typename TComponent>
bool Entity::has_component() {
    auto& registry = registry_.get_registry();
    return registry.all_of<TComponent>(entity_);
}

template <typename TComponent>
auto Entity::remove_component() {
    auto& registry = registry_.get_registry();
    return registry.remove<TComponent>(entity_);
}
