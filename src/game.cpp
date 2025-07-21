#include <game.hpp>
#include <global.hpp>
#include <functions.hpp>

#include <ncurses.h>

#include <string>

Game::Game()
: tilemap(global::seed), running(true), camera_x(0), camera_y(0),
    buffer(nullptr), player(tilemap, 0, 0) {
    getmaxyx(stdscr, global::window_size_y, global::window_size_x);
    buffer = newwin(global::window_size_y, global::window_size_x, 0, 0);
    camera_x = player.x - global::window_size_x / 2;
    camera_y = player.y - global::window_size_y / 2;
}

Game::~Game() {
    if (buffer != nullptr)
        delwin(buffer);
}

void Game::run() {
    refresh();
    while (running) {
        int window_size_x, window_size_y;
        getmaxyx(stdscr, window_size_y, window_size_x);

        if (window_size_x != global::window_size_x || window_size_y != global::window_size_y) {
            global::window_size_x = window_size_x;
            global::window_size_y = window_size_y;
            wresize(buffer, global::window_size_y, global::window_size_x);
        }
        
        draw();

        sleep(global::frame_delay);
        
        input();
    }

    delwin(buffer);
    buffer = nullptr;
}

void Game::draw() {
    for (size_t y = 0; y < global::window_size_y; y++) {
        for (size_t x = 0; x < global::window_size_x; x++) {
            const TileData& tile = tilemap.get_tile(x + camera_x, y + camera_y);
            mvwaddch(buffer, global::window_size_y - 1 - y, x, tile.ch);
        }
    }

    player.draw(buffer, camera_x, camera_y);

    wrefresh(buffer);
}

void Game::input() {
    int ch = getch();

    switch (ch) {
        case 27:
            running = false;
            break;
        case KEY_RIGHT:
            player.interact(1, 0);
            break;
        case KEY_LEFT:
            player.interact(-1, 0);
            break;
        case KEY_UP:
            player.interact(0, 1);
            break;
        case KEY_DOWN:
            player.interact(0, -1);
            break;
        case ' ':
            camera_x = player.x - global::window_size_x / 2;
            camera_y = player.y - global::window_size_y / 2;
            break;
    }

    if (player.x - camera_x == 0)
        camera_x -= global::window_size_x - 2;
    else if (player.x - camera_x == global::window_size_x - 1)
        camera_x += global::window_size_x - 2;

    if (player.y - camera_y == 0)
        camera_y -= global::window_size_y - 2;
    else if (player.y - camera_y == global::window_size_y - 1)
        camera_y += global::window_size_y - 2;
}