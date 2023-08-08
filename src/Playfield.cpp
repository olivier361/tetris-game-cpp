#include <cstdio>
#include "Playfield.hpp"
#include "TetrisGraphics.hpp"

// Constructor creates a Playfield object which is drawn
// with the top left corner of the grid at the given pixel coordinates.
Playfield::Playfield(int xPos, int yPos) : mTetrominoManager(xPos, yPos) {

    // "zero" initialize the play matrix with empty blocks.
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            mMatrix[i][j] = Config::BlockColor::Empty;
        }
    }

    mOffsetX = xPos;
    mOffsetY = yPos;

    mScore = 0;
    mHighScore = 0;
    mLinesCleared = 0;

    Graphics::TetrisGraphics::sDrawableObjectList.push_back(&mTetrominoManager);

    // TODO: Just a test. Remove later.
    mTetrominoManager.setRandomTetromino();
}

// overload the display function from DrawableObject
// to define how the Playfield is to be drawn on screen.
void Playfield::display() {

    // Setup colors needed to draw playfield object.
    const double white[4] = {1.0, 1.0, 1.0, 1.0};           // #FFFFFF white
    const double lightGray[4] = {0.86, 0.86, 0.86, 1.0};    // #dbdbdb light gray
    const double gray[4] = {0.79, 0.79, 0.79, 1.0};         // #c9c9c9 gray
    const double royalBlue[4] = {0.08, 0.44, 1.0, 1.0};     // #1670ff royal blue

    // Draw title and controls text.
    Graphics::TetrisGraphics::drawHeader(110, 76, white, "TETRIS");
    Graphics::TetrisGraphics::drawText(110, 260, white, "CONTROLS:");
    Graphics::TetrisGraphics::drawText(110, 300, white,
"N - Start new game\n\
ESC - Exit game\n\
\n\
W - Rotate clockwise\n\
Q  - Rotate counterclockwise\n\
A  - Move left\n\
D  - Move right\n\
SPACE - Hard drop");

    // Draw score and stats text.
    char scoreStats[128];
    sprintf(scoreStats,"High Score: %7d\nLines Cleared: %3d", mHighScore, mLinesCleared);
    Graphics::TetrisGraphics::drawText(815, 600, white, scoreStats);

    char mainScore[64];
    sprintf(mainScore,"SCORE: %4d", mScore);
    Graphics::TetrisGraphics::drawText(815, 660, white, mainScore);

    // Draw decorative play grid borders (draws square behind main gray play grid).
    Graphics::TetrisGraphics::drawSquare(
        mOffsetX-8,
        mOffsetY-8,
        mOffsetX + (Config::playfieldBlockWidth * Config::blockSizePx) + 8,
        mOffsetY + (Config::playfieldBlockHeight * Config::blockSizePx) + 8,
        royalBlue);
    Graphics::TetrisGraphics::drawSquare(
        mOffsetX-4,
        mOffsetY-4,
        mOffsetX + (Config::playfieldBlockWidth * Config::blockSizePx) + 4,
        mOffsetY + (Config::playfieldBlockHeight * Config::blockSizePx) + 4,
        gray);

    // Draw light gray playing grid background.
    Graphics::TetrisGraphics::drawSquare(
        mOffsetX,
        mOffsetY,
        mOffsetX + (Config::playfieldBlockWidth * Config::blockSizePx),
        mOffsetY+(Config::playfieldBlockHeight * Config::blockSizePx),
        lightGray);

    // draw gray background square grid outline. 
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            Graphics::TetrisGraphics::drawSquareOutline(
                mOffsetX + (j * Config::blockSizePx),
                mOffsetY + (i * Config::blockSizePx),
                mOffsetX + (j * Config::blockSizePx) + Config::blockSizePx,
                mOffsetY + (i * Config::blockSizePx) + Config::blockSizePx,
                2,
                gray);
        }
    }
}
