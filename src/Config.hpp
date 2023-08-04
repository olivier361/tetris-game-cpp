#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace Config {

    // These const variables determine some important parameters for the Tetris game.

    const char* appName;    // The name of the app to be displayed on the window header.

    const int windowSizeX;  // the width of the graphics window in pixels.
    const int windowSizeY;  // the height of the graphics window in pixels.

    const int blockSizePx;  // the width and height of a block in pixels.

    const int playfieldBlockWidth;  // the number of blocks for the grid width.
    const int playfieldBlockHeight; // the number of blocks for the grid height.

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