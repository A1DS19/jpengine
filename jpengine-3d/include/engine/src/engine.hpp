#pragma once
#include "engine/src/application.hpp"
#include "engine/src/input/input-manager.hpp"

#include <chrono>
#include <memory>

struct GLFWwindow;

namespace engine {
class Engine {
public:
    static Engine& get_instance() {
        static Engine instance;
        return instance;
    }

    bool init();
    void run();
    void destroy();

    void set_application(Application* papplication) noexcept { papplication_.reset(papplication); }
    [[nodiscard]] Application* get_application() noexcept { return papplication_.get(); }
    [[nodiscard]] GLFWwindow* get_window() noexcept { return pwindow_; }
    [[nodiscard]] InputManager& get_input_manager() { return input_manager_; }

private:
    Engine() = default;
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    std::unique_ptr<Application> papplication_;
    std::chrono::steady_clock::time_point last_time_point_;
    GLFWwindow* pwindow_ = nullptr;
    InputManager input_manager_;
};

} // namespace engine
