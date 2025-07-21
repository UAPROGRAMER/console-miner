#pragma once

namespace colors {

// setup colors (if not global::use_default_colors)
void setup_colors();

// get color pair (if exists just return else create pair)
unsigned short get_pair(unsigned short fg, unsigned short bg);

}