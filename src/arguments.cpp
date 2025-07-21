#include <arguments.hpp>
#include <global.hpp>

#include <lyra/lyra.hpp>

void parse_arguments(int argc, char* argv[]) {
    bool show_help = false;
    bool use_default_colors = false;
    std::string color_palette = "";
    unsigned long seed = 0;
    unsigned long frame_delay = 16;

    const auto cli = lyra::help(show_help)
        | lyra::opt(use_default_colors)
            ["--use-default-colors"]("For game to use default terminal/ncurses colors.")
        | lyra::opt(color_palette, "color_palette_name")
            ["-p"]["--color-palette"]("Chose color palette (default = ANSI, SOLA).")
        | lyra::opt(seed, "seed")
            ["-s"]["--seed"]("Chose game seed.")
        | lyra::opt(frame_delay, "frame_delay")
            ["-d"]["--frame-delay"]("Chose frame delay in ms (default 16ms ~= (1/60)s).");
    
    const auto result = cli.parse({argc, argv});

    if (!result) {
        std::cerr << "ERROR::ARGUMENTS::INVALID_ARGUMENTS: " << result.message() << '\n';
        exit(1);
    }

    if (show_help) {
        std::cerr << cli << '\n';
        exit(0);
    }

    global::use_default_colors = use_default_colors;

    if (color_palette != "") {
        if (global::COLOR_PALETTE_NAMES.find(color_palette) == global::COLOR_PALETTE_NAMES.end()) {
            std::cerr << "ERROR::ARGUMENTS::INVALID_ARGUMENTS: No palette named \""
                << color_palette << "\" found.\n";
            exit(1);
        }

        global::color_palette = global::COLOR_PALETTE_NAMES.at(color_palette);
    }

    if (seed != 0)
        global::seed = seed;
    
    if (frame_delay != 16)
        global::frame_delay = frame_delay;
}