#include "engine/src/scene/components/player-controller-component.hpp"

#include "GLFW/glfw3.h"
#include "engine/src/engine.hpp"
#include "engine/src/input/input-manager.hpp"

#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>

namespace engine {
void PlayerControllerComponent::update(float deltatime) {
    auto& input_manager = Engine::get_instance().get_input_manager();
    auto rotation = owner_->get_rotation();

    if (input_manager.is_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT)) {
        const auto& old_pos = input_manager.get_mouse_position_old();
        const auto& current_pos = input_manager.get_mouse_position_current();

        float delta_x = current_pos.x - old_pos.x;
        float delta_y = current_pos.y - old_pos.y;

        // rotation around Y axis
        float y_angle = -delta_x * sensitivity_ * deltatime;
        glm::quat y_rot = glm::angleAxis(y_angle, glm::vec3(0.0F, 1.0F, 0.0F));

        // rotation around X axis
        float x_angle = -delta_y * sensitivity_ * deltatime;
        glm::vec3 right = rotation * glm::vec3(1.0F, 0.0F, 0.0F);

        glm::quat x_rot = glm::angleAxis(x_angle, right);

        glm::quat delta_rot = y_rot * x_rot;
        rotation = glm::normalize(delta_rot * rotation);

        owner_->set_rotation(rotation);
    }

    glm::vec3 front = rotation * glm::vec3(0.0F, 0.0F, -1.0F);
    glm::vec3 right = rotation * glm::vec3(1.0F, 0.0F, 0.0F);

    auto position = owner_->get_position();

    if (input_manager.is_key_pressed(GLFW_KEY_W)) {
        position += front * move_speed_ * deltatime;
    }
    if (input_manager.is_key_pressed(GLFW_KEY_A)) {
        position -= right * move_speed_ * deltatime;
    }
    if (input_manager.is_key_pressed(GLFW_KEY_S)) {
        position -= front * move_speed_ * deltatime;
    }
    if (input_manager.is_key_pressed(GLFW_KEY_D)) {
        position += right * move_speed_ * deltatime;
    }

    owner_->set_position(position);
}

} // namespace engine
