---
name: JPEngine-2D Architecture
description: Custom 2D game engine - C++23, SDL2, OpenGL ES 3, Lua scripting, ECS, WASM support
type: project
---

## Overview
JPEngine-2D is a custom 2D game engine built from scratch in C++23. It uses SDL2 + OpenGL ES 3 for rendering, Lua (via Sol2) for scripting, and EnTT under a custom ECS wrapper. It targets Linux, macOS, and WebAssembly (Emscripten).

## Architecture

### Modules (src/ and include/)
- **ecs/** - Entity Component System wrapping EnTT: `Entity`, `Registry`, `Component`
- **rendering/** - BatchRenderer (sprites), TextBatchRenderer (in progress), Camera, Shader, Texture, Font, Vertex, DefaultShaders
- **scripting/** - GLM Lua bindings; other Lua bindings live on their respective classes via `create_lua_bind()` static methods
- **utils/** - AssetLoader (shaders, textures, fonts), MetaUtils (reflection for ECS components)

### Components
Identification, TransformComponent, SpriteComponent, BoxColider, CircleCollider, AnimationComponent, RigidBodyComponent, TextComponent

### Lua Integration
- Game logic lives in `assets/scripts/main.lua`
- Entities and components can be created/queried from Lua
- The Lua script returns an update function called each frame from C++
- Lua bindings registered via `create_lua_bind()` pattern on each class

### Vendor Libraries (bundled in vendor/)
entt, glm, lua, sol2, stb

### Build System
- CMake 3.25+ with a comprehensive Makefile wrapper
- `make build` / `make run` for native, `make wasm` for Emscripten
- Debug builds use ASan + UBSan; Release uses -O3
- Output binary: `bin/main`
- compile_commands.json generated for LSP

### Namespace
All engine code is under `namespace jpengine`.

**Why:** Understanding the full architecture helps provide targeted, context-aware assistance.
**How to apply:** When making changes, respect the module boundaries and existing patterns (e.g., `create_lua_bind()` for new Lua-exposed types, component registration in `register_meta_components()`).
