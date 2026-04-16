#include "rendering/shape-batch-renderer.hpp"

#include "rendering/vertex.hpp"

#include <glm/ext/vector_float2.hpp>

namespace jpengine {

constexpr float PI = 3.1415925f;
constexpr float TWO_PI = PI * 2.F;
constexpr int MAX_SHAPES = 10000;

ShapeRenderer::ShapeRenderer()
    : vao_{0}, vbo_{0}, ebo_{0}, line_vao_{0}, line_vbo_{0}, index_count_{0} {
    initialize();
}

ShapeRenderer::~ShapeRenderer() {
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    glDeleteVertexArrays(1, &vao_);

    glDeleteBuffers(1, &line_vbo_);
    glDeleteVertexArrays(1, &line_vao_);
}

void ShapeRenderer::begin() {
    vertices_.clear();
    line_vertices_.clear();
    indices_.clear();
    index_count_ = 0;
}

void ShapeRenderer::end() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_.size() * sizeof(ShapeVertex), vertices_.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices_.size() * sizeof(unsigned int),
                    indices_.data());

    glBindBuffer(GL_ARRAY_BUFFER, line_vbo_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, line_vertices_.size() * sizeof(ShapeVertex),
                    line_vertices_.data());
}

void ShapeRenderer::render() {
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(line_vao_);
    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(line_vertices_.size()));
}

void ShapeRenderer::add_rectangle(const glm::vec2& position, const glm::vec2& size,
                                  const Color& color) {
    unsigned int i = vertices_.size();
    vertices_.emplace_back(position, color);                          // top left
    vertices_.emplace_back(position + glm::vec2{size.x, 0.F}, color); // top right
    vertices_.emplace_back(position + size, color);                   // botoom right
    vertices_.emplace_back(position + glm::vec2{0, size.y}, color);   // bottom left

    indices_.push_back(i + 0);
    indices_.push_back(i + 1);
    indices_.push_back(i + 2);
    indices_.push_back(i + 2);
    indices_.push_back(i + 3);
    indices_.push_back(i + 0);
}

void ShapeRenderer::add_triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3,
                                 const Color& color) {}

void ShapeRenderer::add_circle(const glm::vec2& center, float radius, const Color& color,
                               int segments) {}

void ShapeRenderer::add_polygon(const std::vector<glm::vec2>& center, const Color& color) {}

void ShapeRenderer::add_line(const glm::vec2& p1, const glm::vec2& p2, const Color& color) {}

void ShapeRenderer::add_wire_rectangle(const glm::vec2& position, const glm::vec2& size,
                                       const Color& color) {}

void ShapeRenderer::add_wire_triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3,
                                      const Color& color) {}

void ShapeRenderer::add_wire_circle(const glm::vec2& center, float radius, const Color& color,
                                    int segments) {}

void ShapeRenderer::add_wire_polygon(const std::vector<glm::vec2>& center, const Color& color) {}

void ShapeRenderer::initialize() {}

} // namespace jpengine
