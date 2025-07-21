#include <global.hpp>
#include <arguments.hpp>
#include <game.hpp>
#include <colors.hpp>

#include <ncurses.h>

#include <cstdlib>
#include <iostream>

void checkup() {
    if (!has_colors()) {
        mvaddstr(0, 0, "Terminal doesn't suport colors.");

        getch();
        endwin();
        std::exit(1);
    }

    if (!can_change_color()) {
        mvaddstr(0, 0, "Terminal doesn't suport changing color.");

        getch();
        endwin();
        std::exit(1);
    }
}

void setup() {
    checkup();

    noecho();
    keypad(stdscr, true);
    start_color();
    cbreak();
    nodelay(stdscr, false);
    noecho();
    curs_set(0);

    if (global::use_default_colors)
        use_default_colors();
    else
        colors::setup_colors();

    //bkgd(' ' | COLOR_PAIR(colors::get_pair(COLOR_WHITE, COLOR_BLACK)));
}

int main(int argc, char* argv[]) {
    parse_arguments(argc, argv);

    initscr();
    setup();

    Game game;
    game.run();

    endwin();

    return 0;
}