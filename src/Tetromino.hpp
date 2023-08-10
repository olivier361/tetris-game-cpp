#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <vector>
#include "Config.hpp"
#include "DrawableObject.hpp"

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
    
        // Constructors.
        Shape() : color(Config::BlockColor::Empty), blocks({}) {};
        Shape(Config::BlockColor c, std::vector<GridLocation> b) : color(c), blocks(b) {}
    }; 


    /// MEMBER VARIABLES ///

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
        {Config::BlockColor::Blue, {{0,0}, {1,0}, {-1,0}, {-1,-1}}},     // J
        {Config::BlockColor::Orange, {{0,0}, {1,0}, {-1,0}, {1,-1}}},    // L
        {Config::BlockColor::Purple, {{0,0}, {0,-1}, {1,0}, {-1,0}}},    // T
        {Config::BlockColor::Yellow, {{0,0}, {0,1}, {1,0}, {1,1}}},     // O
        {Config::BlockColor::Cyan, {{0,0}, {1,0}, {-1,0}, {-2,0}}},      // I
    };

    /// CONSTRUCTORS ///

    // Constructor that creates a Tetromino manager object.
    // This constructor should typically be called in Playfield.
    // The Playfield should pass its origin pixel coordinates as parameters.
    // This Tetromino object manages the active tetromino
    // and how each type of tetromino is represented/drawn.
    Tetromino(double playfieldOrigX = 0.0, double playfieldOrigY = 0.0);

    /// MEMBER FUNCTIONS ///

    // overload the display function from DrawableObject
    // to define how the active block is to be drawn on screen.
    void display();

    // Draws the Tetromino represented by the provided Shape struct
    // at the given GridLocation in grid coordinates.
    void drawTetromino(const GridLocation& location, const Shape& shape);

    // Draws the Tetromino shape currently set as this Tetromino object's
    // mCurShape at mCurLocation on the grid.
    void drawTetromino();

    // Updates the value of mCurShape to one of the Shapes
    // present in the mTetrominoTypes vector, chosen at random.
    void setRandomTetromino();

    // Sets the mCurLocation of the active Tetromino
    // to the starting position.
    void setInitialLocation();

    // Moves the active Tetromino from its current position
    // incremented by the provided x and y parameters.
    // Updates the mCurLocation coordinates.
    //
    // PRECONDITION: The caller must be in charge of checking that the
    // move is valid in regards to the rules of Tetris and the position
    // on the grid. This function does not check if a move is valid.
    void move(int x, int y);

    // Rotates the active Tetromino based on its current orientation.
    // The direction parameter indicates how many subsequent rotations should be done
    // and its sign determine if it rotates clockwise (positive) or counterclockwise (negative).
    // 
    // USAGE:
    // direction > 0 = clockwise ()
    // direction < 0 = counterclockwise
    // EX: rotate(-2) = two counterclockwise rotations.
    //
    // PRECONDITION: The caller must be in charge of checking that the
    // rotation is valid in regards to the position on the grid
    // and not clipping into borders or other blocks.
    // This function does not check if a rotation is valid.
    void rotate(int direction);

}; // End of Tetromino class.


#endif