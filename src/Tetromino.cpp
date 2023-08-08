#include "Tetromino.hpp"
#include "TetrisGraphics.hpp"
#include <cstdlib>
#include <time.h>

/// CONSTRUCTORS ///

// Constructor that creates a Tetromino manager object.
// This constructor should typically be called in Playfield.
// The Playfield should pass its origin pixel coordinates as parameters.
// This Tetromino object manages the active tetromino
// and how each type of tetromino is represented/drawn.
Tetromino::Tetromino(double playfieldOrigX, double playfieldOrigY) : 
    mPlayfieldOriginX(playfieldOrigX), mPlayfieldOriginY(playfieldOrigY) {
    // setupTetrominoTypesVector();

    mCurLocation = {Config::playfieldBlockWidth / 2, 1}; // set initial position to middle of the 2nd row
    mCurShape = {Config::BlockColor::Empty, {}}; // initialize with empty shape.

    // Ensures the sequence of random numbers is different every time
    // the game is played as the random seed is based on the current time.
    srand(time(0)); 
}


/// MEMBER FUNCTIONS ///

// overload the display function from DrawableObject
// to define how the active block is to be drawn on screen.
void Tetromino::display() {
    drawTetromino(mCurLocation, mCurShape);
}

// Draws the Tetromino represented by the provided Shape struct
// at the given GridLocation in grid coordinates.
void Tetromino::drawTetromino(const GridLocation& location, const Shape& shape) {
    for (std::size_t i = 0; i < shape.blocks.size(); ++i) {
        if (location.y + shape.blocks[i].y < 0) {
            // skip drawing any part of the Tetromino that is above the top border.
            // This is needed to allow us to draw a partial Tetromino when it initially
            // Spawns at the top of the screen partially hidden by the top border.
            continue;
        }
        double pixelCoordinatesX = mPlayfieldOriginX + ((location.x + shape.blocks[i].x) * Config::blockSizePx);
        double pixelCoordinatesY = mPlayfieldOriginY + ((location.y + shape.blocks[i].y) * Config::blockSizePx);

        Graphics::TetrisGraphics::drawBlock(pixelCoordinatesX, pixelCoordinatesY, shape.color);
    }
}

// Draws the Tetromino shape currently set as this Tetromino object's
// mCurShape at mCurLocation on the grid.
void Tetromino::drawTetromino() {
    drawTetromino(mCurLocation, mCurShape);
}

// Updates the value of mCurShape to one of the Shapes
// present in the mTetrominoTypes vector, chosen at random.
void Tetromino::setRandomTetromino() {
    std::size_t index = rand() % mTetrominoTypes.size();
    mCurShape = mTetrominoTypes[index];
}
