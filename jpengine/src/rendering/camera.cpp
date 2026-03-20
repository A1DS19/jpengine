#include "rendering/camera.hpp"

#include <glm/ext/matrix_transform.hpp>

using namespace jpengine;

Camera::Camera() : Camera(1366, 768) {}
Camera::Camera(int width, int height)
    : position_(1.0F), camera_matrix_(1.F), projection_matrix_(1.F), width_(width), height_(height),
      scale_(1.F), needs_update_(true) {
    initialize();
}

Camera::~Camera() = default;

void Camera::update() {
    if (!needs_update_) {
        return;
    }

    // translate
    glm::vec3 translate(-position_.x, -position_.y, 0.F);
    camera_matrix_ = glm::translate(projection_matrix_, translate);

    // scale
    glm::vec3 scale(scale_, scale_, 0.F);
    camera_matrix_ *= glm::scale(glm::mat4{1.F}, scale);

    needs_update_ = false;
}

void Camera::initialize() {
    projection_matrix_ = glm::ortho(0.F,                         // left
                                    static_cast<float>(width_),  // right
                                    static_cast<float>(height_), // bottom
                                    0.F,                         // top
                                    -1.F,                        // near
                                    1.F);                        // far
}
