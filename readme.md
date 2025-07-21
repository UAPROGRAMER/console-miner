# Console Miner

Small mining game made in c++ with ncurses.

## Overview

Game made in c++ using ncurses for drawing, lyra for parsing arguments and perling noise library for terrain generation.

## Structure

All source headerfiles are in the include folder and all source file are in src folder. CMakeLists.txt only accounts for cpp and hpp files in this 2 dirrectories.

Extern libraries neccesary for building should be installed or placed in extern folder (exept ncurses).

You can see what every file contains in [Files](#Files).

## Building and executing

For building you need:
- c++ compiler 
- cmake
- ncurses (installed on the system)
- [lyra](https://github.com/bfgroup/Lyra) (on the system or in extern file)
- [perlin-noise-library](https://github.com/Reputeless/PerlinNoise) (on the system or in extern file)

Run:
- cmake -S . -B build
- cmake --build build

Executable will be in dest folder.

## Files

### global.hpp & global.cpp

Contains global variables and color palettes enum. All global variables are in a global namespace.

### arguments.hpp & arguments.cpp

Contains only `parse_arguments` function. Using lyra argument parsing library parses arguments and changes default values if needed. Function is run before ncurse initialized. (run game with -? -h or --help argument to get all possible arguments)

### colors.hpp & colors.cpp

Has a separate colors namespace.

`setup_color` function is called to setup colors acording to selected color palette, it is not called if --use-default-colors option is selected.

`get_color_pair` function is used to not create not needed color_pairs and has a 2d array that keeps track of existing color pairs. Needs ncurses to be active to work.

### functions.hpp & functions.cpp

Contains helper functions.

`sleep` function sleeps for the given number of milliseconds if it is not 0.

### tilemap.hpp & tilemap.cpp

Contains all tile, tileData and tilemap related stuff.

`Coords` class used internaly for saving changes to the world and should not be used as actual cordinates.

`TileData` class used to store data for different tileTypes.

`TileType` enum containing tiletypes.

`get_tile_types` inline function returns const& to a hash map that contains all tiletypes. The map is itself const and static. This is done because tile characters use `get_color_pair` function for colors and that fucntion needs active ncurses to work.

`TileMap` class responsible for generating and saving the map.

### player.hpp & player.cpp

`Player` class.

### game.hpp & game.cpp

Main class `Game`. `Game::run` is an actual entrypoint of the game.

### main.cpp

How this game actualy runs:

- entrypoint in `main`
- parsing arguments with `parse_arguments`
- initializing ncurses
- check terminal for colors
- setup ncurses for the game
- setup colors
- create game class
- call `run` function (main loop of the game)
- exit ncurses