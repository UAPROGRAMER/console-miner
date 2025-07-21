#pragma once

#include <colors.hpp>

#include <ncurses.h>
#include <PerlinNoise.hpp>

#include <unordered_map>

class Coords {
public:
    long x;
    long y;

    Coords(long x, long y);

    bool operator==(const Coords& other) const;
};

namespace std {

template <>
struct hash<Coords> {
    size_t operator()(const Coords& p) const {
        return p.x * 73856093 ^ p.y * 19349663;
    }
};

}

class TileData {
public:
    TileData(chtype ch, bool passible, unsigned char points = 0);

    const chtype ch;
    const bool passible;
    const unsigned char points;
};

enum class TileType {
    FLOOR,
    ROCK,
    DIAMOND
};

inline const std::unordered_map<TileType, TileData>& get_tile_types();

class TileMap {
private:
    siv::PerlinNoise noise;
    std::unordered_map<Coords, TileType> data;
public:
    TileMap(unsigned long seed);

    const TileData& get_tile(long x, long y) const;

    void set_tile(long x, long y, TileType tile);
};