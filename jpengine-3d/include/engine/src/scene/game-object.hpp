#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace engine {

class Scene; // forward decl — needed only for the `friend class Scene;` below

class GameObject {

public:
    virtual ~GameObject() = default;
    virtual void update(float deltatime);
    [[nodiscard]] const std::string& get_name() const noexcept { return name_; }
    void set_name(std::string name) { name_ = std::move(name); }
    [[nodiscard]] GameObject* get_parent() { return parent_; }
    [[nodiscard]] bool get_is_alive() const noexcept { return is_alive_; }
    void mark_for_destroy();

protected:
    GameObject() = default;

private:
    std::string name_;
    GameObject* parent_ = nullptr;
    std::vector<std::unique_ptr<GameObject>> children_;
    bool is_alive_ = true;

    friend class Scene;
};

} // namespace engine
