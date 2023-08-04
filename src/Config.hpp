#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace Config {

    // These const variables determine some important parameters for the Tetris game.

    constexpr char appName[] = "Tetris"; // The name of the app to be displayed on the window header.

    constexpr int windowSizeX = 1280; // the width of the graphics window in pixels.
    constexpr int windowSizeY = 720;  // the height of the graphics window in pixels.

    constexpr int blockSizePx = 30;   // the width and height of a block in pixels.

    constexpr int playfieldBlockWidth = 10;   // the number of blocks for the grid width.
    constexpr int playfieldBlockHeight = 20;  // the number of blocks for the grid height.

    enum class BlockColors {
        Empty,
        Red,
        Green,
        Blue,
        Orange,
        Purple,
        Yellow,
        Cyan,
        Gray
    };

} // End of Config namespace.

#endif