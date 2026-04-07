# jpengine-2d

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

### Native (Linux / macOS)

```bash
# Linux
sudo apt install cmake make g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libgles2

# macOS
brew install cmake sdl2 sdl2_image sdl2_mixer
```

### WebAssembly

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk && ./emsdk install latest && ./emsdk activate latest
source ./emsdk_env.sh
```

## Build

All commands are run from the `jpengine-2d/` directory.

### Native

```bash
make build                  # debug build (default game)
make build GAME=tetris      # debug build for a specific game
make run                    # build and run
make release                # optimized release build
```

### WebAssembly

```bash
make wasm                   # build for browser (default game: platformer)
make wasm GAME=tetris       # build a specific game
make wasm-run               # build and open in browser with emrun
make wasm-run GAME=tetris
```

Output lands in `bin/`: `main.html`, `main.js`, `main.wasm`, `main.data`.

## Project structure

```
jpengine-2d/
├── src/             # Engine C++ sources
├── include/         # Engine C++ headers
│   ├── ecs/         # Entity, Registry, components
│   ├── rendering/   # Shaders, textures, batch renderer
│   ├── inputs/      # Keyboard, mouse, gamepad
│   ├── scripting/   # Lua binding helpers
│   ├── sounds/      # Music and sound players
│   └── utils/       # Asset manager, utilities
├── games/           # One folder per game
│   ├── platformer/
│   │   └── assets/
│   │       ├── scripts/main.lua   # game entry point
│   │       ├── textures/
│   │       ├── fonts/
│   │       ├── music/
│   │       └── soundfx/
│   └── tetris/
│       ├── assets/
│       │   └── scripts/main.lua
│       └── web/
│           ├── shell.html         # custom browser shell
│           └── images/            # images referenced by shell.html
├── vendor/          # Bundled third-party libraries
│   ├── entt/
│   ├── glm/
│   ├── lua/
│   ├── sol2/
│   └── stb/
├── bin/             # Build output
└── CMakeLists.txt
```

## Adding a new game

1. Create `games/<name>/assets/scripts/main.lua` with a `main.update` function.
2. Add any textures, fonts, music, and sound effects under `games/<name>/assets/`.
3. Optionally add `games/<name>/web/shell.html` for a custom browser shell and `games/<name>/web/images/` for web assets.
4. Build with `make wasm GAME=<name>`.

## Lua API

The engine exposes the following globals to Lua scripts:

| Global | Description |
|--------|-------------|
| `Entity()` | Create an entity |
| `Registry()` | Get the ECS registry |
| `AssetManager` | Load/get textures, fonts, music, sound effects |
| `MusicPlayer` | Play, pause, stop, resume music |
| `Keyboard` | Key input (`pressed`, `just_pressed`, `just_released`) |
| `Mouse` | Mouse input (`just_pressed`, `screen_position`) |
| `Gamepad` | Gamepad input (`pressed`, `get_axis_position`) |
| `Camera` | Camera control |
| `j2d_run_script(path)` | Load and execute another Lua file |
| `j2d_measure_text(text, font)` | Measure rendered text width |
| `j2d_right_align_text(text, font, pos)` | Right-align x position |
| `j2d_center_align_text(text, font, pos)` | Center x position |
