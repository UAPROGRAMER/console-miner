#include <ctime>

#include <global.hpp>

namespace global {

bool use_default_colors = false;
int window_size_x = 0;
int window_size_y = 0;
ColorPalette color_palette = ColorPalette::ANSI;
unsigned long seed = std::time(nullptr);
unsigned long frame_delay = 16;
}