# JPEngine-2D

Custom 2D game engine: C++23, SDL2, OpenGL ES 3, Lua (Sol2), EnTT ECS, WASM via Emscripten.

## Build

```bash
make build       # native debug build
make run         # build and run
make wasm        # emscripten/wasm build
make wasm-run    # build and open in browser
```

## Project Structure

- `src/` / `include/` — Engine source (ecs, rendering, scripting, utils)
- `assets/` — Fonts, textures, Lua scripts
- `vendor/` — Bundled deps (entt, glm, lua, sol2, stb)
- `bin/` — Build output

## Conventions

- Namespace: `jpengine`
- Lua bindings: static `create_lua_bind(sol::state&, ...)` on each class
- New components: register in `register_meta_components()` in main.cpp
- C++23 features allowed (designated initializers, etc.)
- Header/source pairs: `include/<module>/foo.hpp` + `src/<module>/foo.cpp`
- Naming: kebab-case files, snake*case members with trailing underscore (e.g. `position*`)
