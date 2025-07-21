#pragma once

#include <string>
#include <unordered_map>

enum class ColorPalette {
    ANSI,
    SOLA,
};

namespace global {
const std::unordered_map<std::string, ColorPalette> COLOR_PALETTE_NAMES = {
    {"ANSI", ColorPalette::ANSI},
    {"SOLA", ColorPalette::SOLA}
};

extern bool use_default_colors;
extern int window_size_x;
extern int window_size_y;
extern ColorPalette color_palette;
extern unsigned long seed;
extern unsigned long frame_delay;
}