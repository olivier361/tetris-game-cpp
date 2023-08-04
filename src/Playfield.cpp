#include "Playfield.hpp"

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

}

