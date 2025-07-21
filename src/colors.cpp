#include <colors.hpp>
#include <global.hpp>

#include <ncurses.h>

namespace colors {

void setup_colors() {
    switch(global::color_palette) {
        case ColorPalette::ANSI:
            init_color(COLOR_BLACK,   0,    0,    0   );
            init_color(COLOR_RED,     1000, 0,    0   );
            init_color(COLOR_GREEN,   0,    1000, 0   );
            init_color(COLOR_YELLOW,  1000, 1000, 0   );
            init_color(COLOR_BLUE,    0,    0,    1000);
            init_color(COLOR_MAGENTA, 1000, 0,    1000);
            init_color(COLOR_CYAN,    0,    1000, 1000);
            init_color(COLOR_WHITE,   1000, 1000, 1000);
            break;
        case ColorPalette::SOLA:
            init_color(COLOR_BLACK,   0,    169,  211 );
            init_color(COLOR_RED,     863,  196,  184 );
            init_color(COLOR_GREEN,   522,  600,  0   );
            init_color(COLOR_YELLOW,  710,  537,  0   );
            init_color(COLOR_BLUE,    149,  545,  827 );
            init_color(COLOR_MAGENTA, 827,  212,  510 );
            init_color(COLOR_CYAN,    165,  631,  596 );
            init_color(COLOR_WHITE,   933,  914,  835 );
            break;
        default:
            exit(1);
    }
}

unsigned short get_pair(unsigned short fg, unsigned short bg) {
    static bool color_pairs[8][8] = {false};
    if (!color_pairs[fg][bg]) {
        init_pair(8 * fg + bg, fg, bg);
        color_pairs[fg][bg] = true;
    }

    return 8 * fg + bg;
}

}