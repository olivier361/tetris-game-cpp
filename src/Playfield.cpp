#include <cstdio>
#include "Playfield.hpp"
#include "TetrisGraphics.hpp"

Playfield::Playfield(int xPos, int yPos) {

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
}

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
    Graphics::TetrisGraphics::drawSquare(490-8, 60-8, 790+8, 660+8, royalBlue);
    Graphics::TetrisGraphics::drawSquare(490-4, 60-4, 790+4, 660+4, gray);

    // Draw light gray playing grid background.
    Graphics::TetrisGraphics::drawSquare(490, 60, 790, 660, lightGray);

    // draw gray background square grid outline. 
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            Graphics::TetrisGraphics::drawSquareOutline(
                490 + (j * Config::blockSizePx),
                60 + (i * Config::blockSizePx),
                490 + (j * Config::blockSizePx) + Config::blockSizePx,
                60 + (i * Config::blockSizePx) + Config::blockSizePx,
                2,
                gray);
        }
    }

    // TODO: Remove later. just a test
    Graphics::TetrisGraphics::drawBlock(490, 60, Config::BlockColor::Orange);
    Graphics::TetrisGraphics::drawBlock(520, 60, Config::BlockColor::Orange);
    Graphics::TetrisGraphics::drawBlock(490, 90, Config::BlockColor::Orange);
    Graphics::TetrisGraphics::drawBlock(520, 90, Config::BlockColor::Orange);
    Graphics::TetrisGraphics::drawBlock(580, 240, Config::BlockColor::Purple);
    Graphics::TetrisGraphics::drawBlock(610, 240, Config::BlockColor::Green);
    Graphics::TetrisGraphics::drawBlock(700, 240, Config::BlockColor::Gray);

}

