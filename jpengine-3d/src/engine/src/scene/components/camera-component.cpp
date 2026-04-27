#include "engine/src/scene/components/camera-component.hpp"

#include "engine/src/scene/game-object.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>

namespace engine {
void CameraComponent::update(float deltatime) {}

[[nodiscard]] glm::mat4 CameraComponent::get_view_matrix() const {
    glm::mat4 mat = glm::mat4(1.0F);
    mat = glm::mat4_cast(owner_->get_rotation());
    mat[3] = glm::vec4(owner_->get_position(), 1.0F);

    if (owner_->get_parent()) {
        mat = owner_->get_parent()->get_world_transform() * mat;
    }

    return glm::inverse(mat);
}

[[nodiscard]] glm::mat4 CameraComponent::get_projection_matrix(float aspect_ratio) const {
    return glm::perspective(glm::radians(fov_), aspect_ratio, near_plane_, far_plane_);
}

} // namespace engine
