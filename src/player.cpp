#include <player.hpp>
#include <global.hpp>

Player::Player(TileMap& tile_map, long x, long y)
: tile_map(tile_map), score(0), x(x), y(y) {}

void Player::interact(int ax, int ay) {
    auto tile = tile_map.get_tile(x + ax, y + ay);
    if (tile.passible) {
        x += ax;
        y += ay;
    } else {
        score += tile.points;
        tile_map.set_tile(x + ax, y + ay, TileType::FLOOR);
    }
}

void Player::draw(WINDOW* window, long camera_x, long camera_y) const {
    if (window != nullptr) {
        mvwaddch(
            window,
            global::window_size_y - 1 - (y - camera_y),
            x - camera_x,
            '@' | A_BOLD | COLOR_PAIR(colors::get_pair(COLOR_RED, COLOR_BLACK))
        );
        std::string score_str = (std::string("score: ") + std::to_string(score)).c_str();
        for (size_t x = 0; x < score_str.length() + 1; x++)
            for (size_t y = 0; y < 2; y++)
                mvwaddch(window, y, x, '=' | COLOR_PAIR(colors::get_pair(COLOR_CYAN, COLOR_BLACK))
                    | A_BOLD);
        mvwaddstr(
            window,
            0,
            0,
            score_str.c_str()
        );
    }
}