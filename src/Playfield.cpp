#include <cstdio>
#include "Playfield.hpp"
#include "TetrisGraphics.hpp"

Playfield::Playfield(int xPos, int yPos) {

    // "zero" initialize the play matrix with empty blocks.
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            mMatrix[i][j] = Config::BlockColors::Empty;
        }
    }

    mOffsetX = xPos;
    mOffsetY = yPos;

    mScore = 0;
    mHighScore = 0;
    mLinesCleared = 0;
}

void Playfield::display() {

    // TODO: Add coordinate offset based on playfield original position.

    // Setup colors needed to draw playfield object.
    const double white[4] = {1.0, 1.0, 1.0, 1.0};           // #FFFFFF white
    const double lightGray[4] = {0.86, 0.86, 0.86, 1.0};    // #dbdbdb light gray
    const double gray[4] = {0.79, 0.79, 0.79, 1.0};         // #c9c9c9 gray
    const double royalBlue[4] = {0.08, 0.44, 1.0, 1.0};     // #1670ff royal blue

    // Draw title and controls text.
    Graphics::TetrisGraphics::drawText(70, 60, white, "Tetris");
    Graphics::TetrisGraphics::drawText(70, 260, white, "CONTROLS:");
    Graphics::TetrisGraphics::drawText(70, 300, white,
"N - Start new game\n\
ESQ - Exit game\n\
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

    // Draw decorative play grid border (draws square behind main gray play grid).
    Graphics::TetrisGraphics::drawSquare(490-8, 60-8, 790+8, 660+8, royalBlue);
    Graphics::TetrisGraphics::drawSquare(490-4, 60-4, 790+4, 660+4, gray);

    // Draw playing grid background.
    Graphics::TetrisGraphics::drawSquare(490, 60, 790, 660, lightGray);

    // draw background square grid outline. 
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

    // TODO: Remove later.
    // Draw test square.
    double red[4] = {1.0, 0.0, 0.0, 1.0};
    Graphics::TetrisGraphics::drawSquare(490, 60, 520, 90, red);


    // double color0[4] = {1.0, 0.0, 0.0, 1.0};
    // // Graphics::TetrisGraphics::drawSquare(0.0, 0.0, 0.3, -0.3, color0); // perfect square. top-left at origin.
    // Graphics::TetrisGraphics::drawSquare(640, 360, 700, 420, color0); // perfect square. top-left at origin.

    // double color1[4] = {0.5, 0.0, 0.5, 1.0};
    // // Graphics::TetrisGraphics::drawSquare(0.1, 0.2, 0.4, 0.6, color1);
    // Graphics::TetrisGraphics::drawSquare(30, 40, 130, 140, color1);

    // double color2[4] = {0.5, 0.5, 0.0, 1.0};
    // // Graphics::TetrisGraphics::drawSquareOutline(0.8, 0.7, 0.95, 0.9, 3, color2);
    // Graphics::TetrisGraphics::drawSquareOutline(1150, 600, 1250, 700, 5, color2);

    // double color3[4] = {1.0, 1.0, 1.0, 1.0}; // white #FFFFFF
    // // Graphics::TetrisGraphics::drawText(-0.6, -0.8, color3, "This is a drawText test");
    // Graphics::TetrisGraphics::drawText(10, 650, color3, "This is a drawText test");

}

