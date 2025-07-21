#pragma once

#include <tilemap.hpp>

class Player {
private:
    TileMap& tile_map;
    unsigned long score;
public:
    long x;
    long y;

    Player(TileMap& tile_map, long x, long y);

    void interact(int ax, int ay);

    void draw(WINDOW* window, long camera_x, long camera_y) const;
};