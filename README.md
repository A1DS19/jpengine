# jpengine

A 2D game engine written in C++ with Lua scripting support, targeting both native Linux/macOS and WebAssembly (browser).

[![Linux Build](https://github.com/A1DS19/cpp-lua-wasm-games/actions/workflows/build-linux.yml/badge.svg)](https://github.com/A1DS19/cpp-lua-wasm-games/actions/workflows/build-linux.yml)
[![WASM Build](https://github.com/A1DS19/cpp-lua-wasm-games/actions/workflows/build-wasm.yml/badge.svg)](https://github.com/A1DS19/cpp-lua-wasm-games/actions/workflows/build-wasm.yml)

## What it does

- Entity-Component-System (ECS) architecture via **EnTT**
- Lua scripting via **sol2** — game logic is written in Lua
- Rendering with **SDL2** + **OpenGL ES 3** (WebGL2 in the browser)
- Math with **GLM**
- Image loading with **stb_image**
- Compiles to WebAssembly with **Emscripten**

## Tech stack

| Library | Purpose |
|---------|---------|
| [EnTT](https://github.com/skypjack/entt) | Entity-Component-System |
| [sol2](https://github.com/ThePhD/sol2) | Lua bindings for C++ |
| [Lua 5.x](https://www.lua.org/) | Scripting language |
| [SDL2](https://www.libsdl.org/) | Window, input, audio |
| [GLM](https://github.com/g-truc/glm) | Math (vectors, matrices) |
| [stb](https://github.com/nothings/stb) | Image loading |
| [Emscripten](https://emscripten.org/) | C++ → WebAssembly compiler |

## Requirements

### Native (Linux)

```bash
sudo apt install cmake make g++ libsdl2-dev libsdl2-image-dev libgles2
```

### WebAssembly

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk && ./emsdk install latest && ./emsdk activate latest
source ./emsdk_env.sh
```

## Build

All commands are run from the `jpengine/` directory.

### Native

```bash
cd jpengine
make build          # debug build
make release        # optimized release build
make run            # build and run
```

### WebAssembly

```bash
cd jpengine
make wasm           # outputs bin/main.html + main.js + main.wasm
make wasm-run       # build and open in browser with emrun
```

## Project structure

```
jpengine/
├── assets/          # Lua scripts, textures, shaders
│   └── scripts/
│       └── main.lua # entry point for game logic
├── include/         # C++ headers
│   ├── ecs/         # Entity, Registry, components
│   └── scripting/   # Lua binding helpers
├── src/             # C++ sources
├── vendor/          # bundled third-party libraries
│   ├── entt/
│   ├── glm/
│   ├── lua/
│   ├── sol2/
│   └── stb/
└── CMakeLists.txt
```
