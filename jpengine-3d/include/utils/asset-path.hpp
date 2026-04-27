#pragma once

#include <filesystem>
#include <string>
#include <string_view>

// JPENGINE_ASSETS_DIR is defined in CMakeLists.txt and expands to the absolute
// path of the project's `assets/` directory at configure time.
#ifndef JPENGINE_ASSETS_DIR
    #error "JPENGINE_ASSETS_DIR is not defined. Configure with CMake."
#endif

namespace utils {

// Returns the absolute path to a file inside the project's assets/ folder.
//   asset_path("textures/wall.png") -> "/abs/path/to/assets/textures/wall.png"
[[nodiscard]] inline std::filesystem::path asset_path(std::string_view relative) {
    return std::filesystem::path{JPENGINE_ASSETS_DIR} / relative;
}

// Same as asset_path() but returns a std::string — convenient for C APIs that
// take const char* (stb_image, fopen, etc.):
//   stbi_load(asset_path_str("textures/wall.png").c_str(), ...);
[[nodiscard]] inline std::string asset_path_str(std::string_view relative) {
    return asset_path(relative).string();
}

} // namespace utils
