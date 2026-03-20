#include "rendering/default-shaders.hpp"

using namespace jpengine;

const char* DefaultShaders::basic_shader_vert = R"(#version 300 es
in vec2 a_pos;
in vec2 a_uvs;
out vec2 frag_uvs;

void main(){
  gl_Position = vec4(a_pos, 0.0f, 1.0f);
  frag_uvs = a_uvs;
}
)";

const char* DefaultShaders::basic_shader_frag = R"(#version 300 es
precision mediump float;
in vec2 frag_uvs;
out vec4 fragColor;
uniform sampler2D u_texture;

void main(){
  fragColor = texture(u_texture, frag_uvs);
}
)";
