# SDL2 + OpenGL ES 3 Rendering — Study Guide

## The big picture

```
Your CPU code (C++)
  └── SDL2          — creates a window and an OpenGL context
  └── OpenGL ES 3   — draws into that window using the GPU
        └── Shaders — small GPU programs that decide positions and colors
```

Everything visible on screen is drawn by the GPU. The CPU only sends data and instructions to it.

---

## Step 1 — SDL2 sets up the window

SDL2 handles the OS-level stuff: creating a window, receiving input events, and managing the OpenGL context.

**Order matters:** GL attributes must be set *before* creating the window, because the driver uses them to select a compatible framebuffer.

```cpp
// 1. Tell SDL we want OpenGL ES 3.0
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

// 2. Create the window (must come AFTER GL attributes)
p_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 600,
                             SDL_WINDOW_OPENGL);  // <-- flag required

// 3. Create the GL context bound to that window
gl_context = SDL_GL_CreateContext(p_window);

// 4. Enable vsync (optional but recommended)
SDL_GL_SetSwapInterval(1);
```

The **GL context** is the object that holds all GPU state (which shader is active, what buffers exist, etc.). Without it, no GL calls work.

---

## Step 2 — Upload geometry to the GPU

The GPU can't access normal CPU memory directly. You have to explicitly upload vertex data into a **VBO** (Vertex Buffer Object) — a chunk of memory that lives on the GPU.

```
CPU RAM:  float vertices[] = { -0.5, -0.5, 0.0,
                                 0.5, -0.5, 0.0,
                                 0.0,  0.5, 0.0 }
                                 ^--- XYZ positions in clip space (-1..1)
                                      uploaded once at startup ─────────────┐
                                                                             ▼
GPU VRAM: [VBO]  raw bytes of the vertex array
          [VAO]  layout descriptor: "3 floats per vertex, at attribute slot 0"
```

```cpp
glGenVertexArrays(1, &vao);   // create VAO — records how to read the VBO
glGenBuffers(1, &vbo);        // create VBO — raw buffer on the GPU
glBindVertexArray(vao);       // start recording layout into VAO
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//                                                         ^
//                                         hint: data won't change, store in fast VRAM

glVertexAttribPointer(0,          // attribute slot 0 → matches "in vec3 a_pos" in shader
                      3,          // 3 components per vertex (x, y, z)
                      GL_FLOAT,   // each component is a float
                      GL_FALSE,   // don't normalize
                      3 * sizeof(float),  // stride: bytes between vertices
                      nullptr);   // offset: start at byte 0
glEnableVertexAttribArray(0);
```

### Why VAO + VBO?

- **VBO** = the raw data (just bytes)
- **VAO** = the description of that data (how many floats, which slot, what stride)

When you draw, you bind the VAO and the GPU knows exactly how to feed the VBO data into the vertex shader.

---

## Step 3 — Shaders

Shaders are small programs that run on the GPU, written in **GLSL ES**.

Two shaders are always required:

```
For each vertex ──► Vertex shader   — WHERE on screen does this point go?
For each pixel  ──► Fragment shader — WHAT COLOR is this pixel?
```

### Vertex shader

```glsl
#version 300 es
in vec3 a_pos;             // input: one XYZ vertex from the VBO (slot 0)
void main() {
    gl_Position = vec4(a_pos, 1.0);  // output: position in clip space
}
```

**Clip space** maps -1..+1 to the screen edges:
```
(-1, 1) ──────── (1, 1)
   |                 |
   |    (0, 0)       |
   |                 |
(-1,-1) ──────── (1,-1)
```

So vertices at `-0.5,-0.5` / `0.5,-0.5` / `0.0,0.5` produce a triangle centered on screen.

### Fragment shader

```glsl
#version 300 es
precision mediump float;   // required in GLES — declare float precision
out vec4 fragColor;        // output: RGBA color for this pixel
void main() {
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);  // solid red (R=1, G=0, B=0, A=1)
}
```

### GLSL ES rules (strict — will break silently in WebGL if ignored)

| Rule | Wrong | Correct |
|---|---|---|
| `#version` must be line 1 | blank line before it | `#version 300 es` at top |
| No `f` suffix on floats | `1.0f` | `1.0` |
| Precision required in frag | _(missing)_ | `precision mediump float;` |

### Compiling shaders at runtime

```
glCreateShader(GL_VERTEX_SHADER)   — allocate shader object on GPU
glShaderSource(shader, 1, &src, nullptr)   — upload GLSL source text
glCompileShader(shader)   — driver compiles it (errors retrievable via glGetShaderInfoLog)

glCreateProgram()   — allocate the final linked program
glAttachShader(program, vert)
glAttachShader(program, frag)
glLinkProgram(program)   — link vert + frag together (errors via glGetProgramInfoLog)
```

Shader compilation happens **at runtime** on the GPU driver — not at build time. Always check for errors after compile and link.

---

## Step 4 — The game loop

Every frame follows the same sequence:

```
┌─────────────────────────────────────────────────────┐
│ 1. Poll SDL events   (input, window close)          │
│ 2. Clear the screen                                 │
│ 3. Set viewport      (map clip space to pixels)     │
│ 4. glUseProgram      (activate shaders)             │
│ 5. glBindVertexArray (activate geometry)            │
│ 6. glDrawArrays      (GPU runs shaders → pixels)    │
│ 7. SDL_GL_SwapWindow (flip back buffer to screen)   │
└─────────────────────────────────────────────────────┘
```

```cpp
glClearColor(0.0, 0.0, 0.0, 1.0);   // set background color (black)
glClear(GL_COLOR_BUFFER_BIT);        // fill screen with background color

glViewport(0, 0, width, height);     // map -1..1 to 0..width, 0..height

glUseProgram(shader_program);        // activate our shaders
glBindVertexArray(vao);              // activate our geometry

glDrawArrays(GL_TRIANGLES, 0, 3);    // draw vertices 0,1,2 as a triangle

SDL_GL_SwapWindow(p_window);         // present — show finished frame
```

**Double buffering:** you draw into a hidden back buffer, then `SwapWindow` flips it to screen atomically so there's no tearing.

---

## WebAssembly (Emscripten) differences

### Main loop

The browser's JS event loop cannot be blocked. `while(true)` would freeze the tab entirely.

```cpp
// Desktop:
while (true) { game_loop(); }

// WASM:
emscripten_set_main_loop(game_loop, 0, 1);
// The browser calls game_loop() once per animation frame (~60fps)
```

### WebGL2 = OpenGL ES 3

WebGL2 exposes the same GLES3 API. Enable it in CMake link flags:
```
-sUSE_WEBGL2=1 -sFULL_ES3=1
```

### Asset loading

The browser has no real filesystem. Files are bundled into a virtual FS at build time:
```
--preload-file assets@/assets
```
This packages the `assets/` folder so Lua and shaders can be loaded with the same relative paths at runtime.

### Exceptions

Emscripten disables C++ exceptions by default (`-fignore-exceptions`). sol2 requires them. Enable wasm-native exceptions:
```
-fwasm-exceptions   (compile + link flags, for both main and lua targets)
```

### Summary table

| Topic | Native Linux | WASM |
|---|---|---|
| OpenGL | GLES3 via Mesa | WebGL2 (same API) |
| Main loop | `while(true)` | `emscripten_set_main_loop` |
| Assets | relative paths | `--preload-file` virtual FS |
| Exceptions | normal | `-fwasm-exceptions` |
| GLSL floats | `1.0f` tolerated | `1.0f` rejected — use `1.0` |
| `#version` position | flexible | must be line 1, no leading newline |
