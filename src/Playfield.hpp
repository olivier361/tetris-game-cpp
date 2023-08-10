#ifndef PLAYFIELD_HPP
#define PLAYFIELD_HPP

#include "Config.hpp"
#include "DrawableObject.hpp"
#include "Tetromino.hpp"
#include "OverlayManager.hpp"

class Playfield : public Graphics::DrawableObject {

    /// MEMBER VARIABLES ///

    public:

    bool mIsFirstStart;         // True if a game has never been played since program launched. (Don't display game over on first start).
    bool mIsGameRunning;        // True if the game is running (i.e. should make Tetrominos fall and accept player input).
    bool mIsGameOver;           // True if the player has not started a game or has ended. Used to determine if the player can pause/unpause.
    bool mIsNextDropScheduled;  // True if a timer has already been started. Avoids calling duplicate timers.

    private:

    // The matrix that keeps track of what blocks are currently on the playing grid.
    Config::BlockColor mMatrix[Config::playfieldBlockHeight][Config::playfieldBlockWidth];

    Tetromino mTetrominoManager;    // The Tetromino object associated with this Playfield instance.
    OverlayManager mOverlayManager; // The OverlayManager object associated with this Playfield instance. 

    int mOffsetX; // The X pixel coordinate offset for the top-right corner of the playfield object.
    int mOffsetY; // The Y pixel coordinate offset for the top-right corner of the playfield object.

    int mScore;         // Keeps track of the current score.
    int mHighScore;     // Keeps track of the highest recorded score since the program was launched.
    int mLinesCleared;  // Keeps track of the total amount of lines cleared in the current game.


    /// CONSTRUCTORS ///

    public:

    // Constructor creates a Playfield object which is drawn
    // with the top left corner of the grid at the given pixel coordinates.
    Playfield(int xPos = 0, int yPos = 0);


    /// MEMBER FUNCTIONS ///

    // overload the display function from DrawableObject
    // to define how the Playfield is to be drawn on screen.
    void display();

    // Pauses/Unpauses the game if it is not in a game over state.
    // Returns the status of mIsGameRunning after performing the toggle.
    bool pauseToggle();

    // Move the active Tetromino to the left
    // if there are no collisions.
    void moveLeft();

    // Move the active Tetromino to the right
    // if there are no collisions.
    void moveRight();

    // Drops the active Tetromino as far down as possible until either
    // a collision with another block or the bottom of the matrix occurs.
    void hardDrop();

    // Checks if there is a collision at an N cells offset on the x axis on the side of the active Tetromino.
    // Returns true if there is a collision with a block or the side border of the matrix and false otherwise.
    // Ex: n = 1: checks for collision one to the right.
    //     n = -1: checks for collision one to the left.
    bool checkSideCollision(int n);
    
    // Checks if there is a collision at N cells below the active Tetromino.
    // Returns true if there is a collision with a block or the bottom of the matrix
    // and false otherwise.
    bool checkBottomCollision(int n);

    // Drops the active Tetromino by one cell if no collisions are to occur below.
    // Returns true if the drop is successful and false otherwise.
    bool tryDropOne();

    // Based on the location of the active Tetromino, returns the computed
    // max amount of cells the active Tetromino is safely allowed to drop without collisions.
    // This is used to compute the location for a hard drop or a ghost block.
    int computeMaxDrop();

    // Based on the given shape and location of the active Tetromino,
    // Updates the matrix cell values to match the overlaying Tetromino.
    void saveTetrominoToMatrix();

    // Checks the Matrix for any full rows. If full rows are found, the row is emptied
    // and all lines above are shifted down. Points are also awarded for cleared lines.
    void clearFullLines();

    // Performs the setup required to initiate a new game
    // and cleanup states of any previous game.
    void startGame();

    // Checks to see if the top row of the mMatrix contains a block.
    // If so returns true that the game is over.
    bool isGameOver();

    // Upon being called from a timer, makes the active Tetromino
    // drop if possible. If not possible, the Tetromino coordinates
    // are saved to the matrix and a new active Tetromino is spawned.
    void onDropTimer(int value);

    /// HELPER FUNCTIONS ///

    private:

    // This function increments the mScore variable while also updating
    // mHighScore if the score is greater than the current high score.
    // NOTE: mScore should never be incremented directly. It should always
    // use this function to ensure the high score remains accurate.
    void incrementScoreAndHighScore(int amount);

    // Sets all the entries of mMatrix to Config::BlockColor::Empty.
    void flushMatrix();

    // Returns true if the line at rowIndex in the mMatrix is filled with blocks.
    bool isLineFull(int rowIndex);

    // Clears the line at the given row index in the mMatrix
    // and shift all lines above it down by one row.
    void shiftLinesDown(int rowIndex);

}; // End of Playfield class.

#endif