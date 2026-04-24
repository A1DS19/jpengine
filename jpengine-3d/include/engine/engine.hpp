#pragma once

// Umbrella header — pulls in the full public engine API.
// User code should prefer this include over the individual headers.
//
// The IWYU "export" pragmas tell clangd/include-what-you-use that these
// re-exports are intentional — they silence the "included header is not
// used directly" warning in this file.

#include "engine/src/application.hpp"             // IWYU pragma: export
#include "engine/src/engine.hpp"                  // IWYU pragma: export
#include "engine/src/graphics/graphics-api.hpp"   // IWYU pragma: export
#include "engine/src/graphics/shader-program.hpp" // IWYU pragma: export
#include "engine/src/graphics/vertex-layout.hpp"  // IWYU pragma: export
#include "engine/src/input/input-manager.hpp"     // IWYU pragma: export
#include "engine/src/render/material.hpp"         // IWYU pragma: export
#include "engine/src/render/mesh.hpp"             // IWYU pragma: export
#include "engine/src/render/render-queue.hpp"     // IWYU pragma: export
#include "engine/src/scene/game-object.hpp"       // IWYU pragma: export
#include "engine/src/scene/scene.hpp"             // IWYU pragma: export
