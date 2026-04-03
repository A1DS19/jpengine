#pragma once

#include "rendering/vertex.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <string_view>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GLES3/gl3.h>
#endif

#include <memory>
#include <vector>

namespace jpengine {
class Font;

struct TextBatch {
    GLuint num_vertices_{0};
    GLuint texture_id_{0};
    GLuint offset_{0};
};

struct TextGlyph {
    std::string text_{""};
    glm::vec2 position_{0.F};
    Color color_{255, 255, 255, 255};
    glm::mat4 model_{1.F};
    std::shared_ptr<Font> pfont_{nullptr};
};

class TextBatchRenderer {

public:
    TextBatchRenderer();
    ~TextBatchRenderer();
    void begin();
    void end();
    void add_text(std::string_view text, std::shared_ptr<Font>& pfont, const glm::vec2& position,
                  const Color& color = Color{255, 255, 255, 255},
                  const glm::mat4& model = glm::mat4{1.F});
    void render();

private:
    GLuint vao_;
    GLuint vbo_;
    std::vector<std::unique_ptr<TextGlyph>> text_glyphs_{};
    std::vector<std::unique_ptr<TextBatch>> text_batches_{};

    void init();
    void create_batches();
};

} // namespace jpengine
