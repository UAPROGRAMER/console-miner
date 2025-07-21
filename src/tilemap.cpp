#include <tilemap.hpp>

Coords::Coords(long x, long y)
: x(x), y(y) {}

bool Coords::operator==(const Coords& other) const {
    return x == other.x && y == other.y;
}

TileData::TileData(chtype ch, bool passible, unsigned char points)
: ch(ch), passible(passible), points(points) {}

inline const std::unordered_map<TileType, TileData>& get_tile_types() {
    static const std::unordered_map<TileType, TileData> tiles = {
        {TileType::FLOOR,
            TileData('.' | A_BOLD | COLOR_PAIR(colors::get_pair(COLOR_WHITE, COLOR_BLACK)),
                true
            )
        },
        {TileType::ROCK,
            TileData('#' | A_BOLD | COLOR_PAIR(colors::get_pair(COLOR_WHITE, COLOR_BLACK)),
                false
            )
        },
        {TileType::DIAMOND,
            TileData('*' | A_BOLD | COLOR_PAIR(colors::get_pair(COLOR_BLACK, COLOR_BLUE)),
                false,
                10
            )
        },
    };
    return tiles;
}

TileMap::TileMap(unsigned long seed)
: noise(seed) {}

const TileData& TileMap::get_tile(long x, long y) const {
    auto it = data.find({x, y});
    if (it != data.end())
        return get_tile_types().at(it->second);

    double noise_value = 1.1 * noise.noise2D_01(
        static_cast<double>(x) / (M_LN10f128 * 40.0),
        static_cast<double>(y) / (M_LN10f128 * 40.0)
    ) + 1.55 * noise.noise2D_01(
        static_cast<double>(x) / (M_PI * 4.0) + (M_PI * 40.0),
        static_cast<double>(y) / (M_PI * 4.0) + (M_PI * 40.0)
    ) + 0.35 * noise.noise2D_01(
        static_cast<double>(x) / (M_2_SQRTPI * 1.0) + (M_2_SQRTPI * 100.0),
        static_cast<double>(y) / (M_2_SQRTPI * 1.0) + (M_2_SQRTPI * 100.0)
    );
    noise_value /= 3;
    TileType type = (noise_value > 0.55) ? TileType::ROCK : TileType::FLOOR;
    if (type == TileType::ROCK) {
        double noise_value = noise.noise2D_01(
            static_cast<double>(x) / (M_LOG10Ef64x * 6.0) + (M_LOG10Ef64x * 600.0),
            static_cast<double>(y) / (M_LOG10Ef64x * 6.0) + (M_LOG10Ef64x * 600.0)
        );

        if (noise_value > 0.75)
            type = TileType::DIAMOND;
    }

    return get_tile_types().at(type);
}

void TileMap::set_tile(long x, long y, TileType tile) {
    auto it = data.find({x, y});
    if (it != data.end())
        it->second = tile;
    else
        data.insert({{x, y}, tile});
}