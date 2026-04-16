#pragma once

#include <glm/ext/vector_float2.hpp>
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GLES3/gl3.h>
#endif
#include "vertex.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace jpengine {

class ShapeRenderer {
public:
    ShapeRenderer();
    ~ShapeRenderer();

    void begin();
    void end();
    void render();

    // solid shapes
    void add_rectangle(const glm::vec2& position, const glm::vec2& size, const Color& color);
    void add_triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3,
                      const Color& color);
    void add_circle(const glm::vec2& center, float radius, const Color& color, int segments = 32);
    void add_polygon(const std::vector<glm::vec2>& center, const Color& color);
    void add_line(const glm::vec2& p1, const glm::vec2& p2, const Color& color);

    // wireframe shapes
    void add_wire_rectangle(const glm::vec2& position, const glm::vec2& size, const Color& color);
    void add_wire_triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3,
                           const Color& color);
    void add_wire_circle(const glm::vec2& center, float radius, const Color& color,
                         int segments = 32);
    void add_wire_polygon(const std::vector<glm::vec2>& center, const Color& color);

private:
    void initialize();

private:
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;

    GLuint line_vao_;
    GLuint line_vbo_;

    std::vector<ShapeVertex> vertices_;
    std::vector<ShapeVertex> line_vertices_;
    std::vector<unsigned int> indices_;

    unsigned int index_count_;
};

} // namespace jpengine
