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

    double color1[4] = {0.5, 0.0, 0.5, 1.0};
    Graphics::TetrisGraphics::drawSquare(0.1, 0.2, 0.4, 0.6, color1);

    double color2[4] = {0.5, 0.5, 0.0, 1.0};
    Graphics::TetrisGraphics::drawSquareOutline(0.8, 0.7, 0.95, 0.9, 3, color2);

}

