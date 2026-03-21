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
