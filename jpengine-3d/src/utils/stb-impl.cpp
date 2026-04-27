// Single translation unit that emits the stb_image function bodies. Every
// other .cpp can `#include <stb_image.h>` normally — only this file defines
// the implementation macro. Defining it in more than one file produces
// multiple-symbol linker errors.

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
