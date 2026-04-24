#include "engine/src/scene/game-object.hpp"

namespace engine {

void GameObject::update(float deltatime) {
    for (auto it = children_.begin(); it != children_.end();) {
        if ((*it)->is_alive_) {
            (*it)->update(deltatime);
            ++it;
        } else {
            it = children_.erase(it);
        }
    }
}

void GameObject::mark_for_destroy() {
    is_alive_ = false;
}

} // namespace engine
