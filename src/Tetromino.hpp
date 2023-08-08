#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <vector>
#include "Config.hpp"
#include "DrawableObject.hpp"

// TODO: Add code here.

class Tetromino : public Graphics::DrawableObject {

    /// TYPES ///
    
    public:

    // A type to represent the location and color of a single block on the grid.
    // NOTE: A block refers to the individual squares that make up a Tetromino.
    struct GridLocation {
        int x;
        int y;
    };

    // A type to store the necessary information to
    // represent the shape and color of a Tetromino.
    struct Shape {
        Config::BlockColor color; // the color of this type of shape.
        std::vector<GridLocation> blocks; // stores the coordinates of all blocks that make up the shape.
    
        Shape() : color(Config::BlockColor::Empty), blocks({}) {};
        Shape(Config::BlockColor c, std::vector<GridLocation> b) : color(c), blocks(b) {}
    }; 
    // typedef Shape;


    /// MEMBER VARIABLES ///

    // const Shape test = {Config::BlockColor::Red, {}};

    const double mPlayfieldOriginX; // the pixel coordinates of the top-left corner of the playing grid (passed when constructed).
    const double mPlayfieldOriginY; // the pixel coordinates of the top-left corner of the playing grid (passed when constructed).

    GridLocation mCurLocation;  // the current location of the active Tetromino in grid coordinates.
    Shape mCurShape;            // the Tetromino shape of the currently active piece.

    // TODO: add mCurRotation which keeps track of current rotation (or just modify values in mCurShape instead).

    // A vector that stores representations of each supported Tetromino type (i.e. Z,S,J,L,T,O,I Tetrominos).
    // Each Tetromino type is represented as a Shape (i.e. a color and a vector of block GridLocations
    // relative to the origin of the shape (0,0)).
    const std::vector<Shape> mTetrominoTypes = {
        {Config::BlockColor::Red, {{0,0}, {0,1}, {1,1}, {-1,0}}},       // Z
        {Config::BlockColor::Green, {{0,0}, {0,1}, {-1,1}, {1,0}}},     // S
        {Config::BlockColor::Blue, {{0,0}, {0,1}, {0,-1}, {-1,1}}},     // J
        {Config::BlockColor::Orange, {{0,0}, {0,1}, {0,-1}, {1,1}}},    // L
        {Config::BlockColor::Purple, {{0,0}, {0,1}, {1,0}, {-1,0}}},    // T
        {Config::BlockColor::Yellow, {{0,0}, {0,1}, {1,0}, {1,1}}},     // O
        {Config::BlockColor::Cyan, {{0,0}, {0,-1}, {0,1}, {0,2}}},      // I
    };

    /// CONSTRUCTORS ///

    Tetromino(double playfieldOrigX = 0.0, double playfieldOrigY = 0.0);

    /// MEMBER FUNCTIONS ///

    // overload the display function from DrawableObject
    // to define how the active block is to be drawn on screen.
    void display();

    // void setupTetrominoTypesVector();

    void drawTetromino(const GridLocation& location, const Shape& shape);
    void drawTetromino();

    void setRandomTetromino();


}; // End of Tetromino class.


#endif