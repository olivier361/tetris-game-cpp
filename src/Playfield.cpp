#include "Playfield.hpp"
#include "TetrisGraphics.hpp"

Playfield::Playfield(int xPos, int yPos) {

    // "zero" initialize the play matrix with empty blocks.
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            mMatrix[i][j] = Config::BlockColors::Empty;
        }
    }

    mScore = 0;
    mHighScore = 0;
    mLinesCleared = 0;
}

void Playfield::display() {

    // TODO: Draw the playfield using methods from TetrisGraphics.hpp

    // TODO: Add coordinate offset based on playfield original position.

    double color0[4] = {1.0, 0.0, 0.0, 1.0};
    // Graphics::TetrisGraphics::drawSquare(0.0, 0.0, 0.3, -0.3, color0); // perfect square. top-left at origin.
    Graphics::TetrisGraphics::drawSquare(640, 360, 700, 420, color0); // perfect square. top-left at origin.

    double color1[4] = {0.5, 0.0, 0.5, 1.0};
    // Graphics::TetrisGraphics::drawSquare(0.1, 0.2, 0.4, 0.6, color1);
    Graphics::TetrisGraphics::drawSquare(30, 40, 130, 140, color1);

    double color2[4] = {0.5, 0.5, 0.0, 1.0};
    // Graphics::TetrisGraphics::drawSquareOutline(0.8, 0.7, 0.95, 0.9, 3, color2);
    Graphics::TetrisGraphics::drawSquareOutline(1150, 600, 1250, 700, 5, color2);

    double color3[4] = {1.0, 1.0, 1.0, 1.0};
    // Graphics::TetrisGraphics::drawText(-0.6, -0.8, color3, "This is a drawText test");
    Graphics::TetrisGraphics::drawText(10, 650, color3, "This is a drawText test");

}

