#include "ecs/component.hpp"
#include "ecs/registry.hpp"

using namespace jpengine;

template <typename TContext>
TContext Registry::add_to_context(TContext context) {
    return registry_->ctx().emplace<TContext>(context);
}

template <typename TContext>
[[nodiscard]] TContext& Registry::get_context() {
    return registry_->ctx().get<TContext>();
}

template <typename TContext>
[[nodiscard]] TContext* Registry::try_get_context() {
    return registry_->ctx().find<TContext>();
}

template <typename TContext>
bool Registry::remove_context(TContext context) {
    return registry_->ctx().erase<TContext>(context);
}

template <typename TContext>
bool Registry::has_context(TContext context) {
    return registry_->ctx().contains<TContext>(context);
}

template <typename TComponent>
void Registry::register_meta_component() {
    using namespace entt::literals;

    entt::meta_factory<TComponent>()
        .type(entt::type_hash<TComponent>::value())
        .template func<&jpengine::add_component_to_view<TComponent>>("add_component_to_view"_hs)
        .template func<&jpengine::exclude_component_from_view<TComponent>>(
            "exclude_component_from_view"_hs);
}

namespace jpengine {

template <typename TComponent>
entt::runtime_view& add_component_to_view(Registry* pregistry, entt::runtime_view& view) {
    return view.iterate(pregistry->get_registry().storage<TComponent>());
}

template <typename TComponent>
void exclude_component_from_view(Registry* pregistry, entt::runtime_view* view) {
    view->exclude(pregistry->get_registry().storage<TComponent>());
}

} // namespace jpengine
