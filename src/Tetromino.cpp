#include "Tetromino.hpp"
#include "TetrisGraphics.hpp"
#include <cstdlib> // for rand function
#include <time.h> // for time function
#include <iostream> // TODO: for cout test

// TODO: Add code here.

/// CONSTRUCTORS ///

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

// void Tetromino::setupTetrominoTypesVector() {
//     std::vector<GridLocation> z = {{0,0}, {0,1}, {1,1}, {-1,0}};
//     std::vector<GridLocation> s = {{0,0}, {0,1}, {-1,1}, {1,0}};
//     // TODO: Add remaining
//     std::vector<GridLocation> o = {{0,0}, {0,1}, {1,0}, {1,1}};

//     Shape test(Config::BlockColor::Red, {{0,0}, {0,1}, {1,1}, {-1,0}});

// }

void Tetromino::drawTetromino(const GridLocation& location, const Shape& shape) {
    // std::cout << "I am in drawTetromino\n";
    for (std::size_t i = 0; i < shape.blocks.size(); ++i) {
        if (location.y + shape.blocks[i].y < 0) {
            // skip drawing any part of the Tetromino that is above the top border.
            // This is needed to allow us to draw a partial Tetromino when it initially
            // Spawns at the top of the screen partially hidden by the top border.
            continue;
        }
        double pixelCoordinatesX = mPlayfieldOriginX + ((location.x + shape.blocks[i].x) * Config::blockSizePx);
        double pixelCoordinatesY = mPlayfieldOriginY + ((location.y + shape.blocks[i].y) * Config::blockSizePx);

        // std::cout << "Calling drawBlock\n";
        Graphics::TetrisGraphics::drawBlock(pixelCoordinatesX, pixelCoordinatesY, shape.color);
    }
}

void Tetromino::drawTetromino() {
    drawTetromino(mCurLocation, mCurShape);
}

void Tetromino::setRandomTetromino() {
    std::size_t index = rand() % mTetrominoTypes.size();
    mCurShape = mTetrominoTypes[index];
}
