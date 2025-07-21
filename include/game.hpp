#pragma once

#include <tilemap.hpp>
#include <player.hpp>

class Game {
private:
    TileMap tilemap;
    bool running;
    long camera_x;
    long camera_y;
    WINDOW* buffer;
    Player player;

    void draw();

    void input();
public:
    Game();
    ~Game();

    void run();
};