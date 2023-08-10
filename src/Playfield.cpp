#include <cstdio>
#include "Playfield.hpp"
#include "TetrisGraphics.hpp"
#include "TetrisInput.hpp"

/// CONSTRUCTORS ///

// Constructor creates a Playfield object which is drawn
// with the top left corner of the grid at the given pixel coordinates.
Playfield::Playfield(int xPos, int yPos) : mTetrominoManager(xPos, yPos), mOverlayManager() {

    // "zero" initialize the play matrix with empty blocks.
    flushMatrix();

    mOffsetX = xPos;
    mOffsetY = yPos;

    mScore = 0;
    mHighScore = 0;
    mLinesCleared = 0;

    mIsFirstStart = true;
    mIsGameRunning = false;
    mIsGameOver = true;
    mIsNextDropScheduled = false;

    // The push_back order determines what is drawn first (i.e. depth)
    Graphics::TetrisGraphics::sDrawableObjectList.push_back(&mTetrominoManager);
    Graphics::TetrisGraphics::sDrawableObjectList.push_back(&mOverlayManager);
}


/// MEMBER FUNCTIONS ///

// overload the display function from DrawableObject
// to define how the Playfield is to be drawn on screen.
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
P - Pause game\n\
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
    Graphics::TetrisGraphics::drawSquare(
        mOffsetX-8,
        mOffsetY-8,
        mOffsetX + (Config::playfieldBlockWidth * Config::blockSizePx) + 8,
        mOffsetY + (Config::playfieldBlockHeight * Config::blockSizePx) + 8,
        royalBlue);
    Graphics::TetrisGraphics::drawSquare(
        mOffsetX-4,
        mOffsetY-4,
        mOffsetX + (Config::playfieldBlockWidth * Config::blockSizePx) + 4,
        mOffsetY + (Config::playfieldBlockHeight * Config::blockSizePx) + 4,
        gray);

    // Draw light gray playing grid background.
    Graphics::TetrisGraphics::drawSquare(
        mOffsetX,
        mOffsetY,
        mOffsetX + (Config::playfieldBlockWidth * Config::blockSizePx),
        mOffsetY+(Config::playfieldBlockHeight * Config::blockSizePx),
        lightGray);

    // Draw gray background square grid outline. 
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            Graphics::TetrisGraphics::drawSquareOutline(
                mOffsetX + (j * Config::blockSizePx),
                mOffsetY + (i * Config::blockSizePx),
                mOffsetX + (j * Config::blockSizePx) + Config::blockSizePx,
                mOffsetY + (i * Config::blockSizePx) + Config::blockSizePx,
                2,
                gray);
        }
    }

    // For each cell in the matrix, draw Tetromino blocks that are saved in the matrix
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {

            if (mMatrix[i][j] != Config::BlockColor::Empty) {
                // Draw block at current matrix position
                // if a block is placed there.
                Graphics::TetrisGraphics::drawBlock(
                    mOffsetX + (j * Config::blockSizePx),
                    mOffsetY + (i * Config::blockSizePx),
                    mMatrix[i][j]);
            }
        }
    }

}

// Pauses/Unpauses the game if it is not in a game over state.
// Returns the status of mIsGameRunning after performing the toggle.
bool Playfield::pauseToggle() {
    if (!mIsGameOver) {
        mIsGameRunning = !mIsGameRunning;
        mOverlayManager.mSetPauseOverlay = !mIsGameRunning;
    }
    return mIsGameRunning;
}

// Move the active Tetromino to the left
// if there are no collisions.
void Playfield::moveLeft() {
    if (!mIsGameRunning) {return;}

    if (!checkSideCollision(-1)) {
        mTetrominoManager.move(-1,0);
    }
}

// Move the active Tetromino to the right
// if there are no collisions.
void Playfield::moveRight() {
    if (!mIsGameRunning) {return;}

    if (!checkSideCollision(1)) {
        mTetrominoManager.move(1,0);
    }
}

// Drops the active Tetromino as far down as possible until either
// a collision with another block or the bottom of the matrix occurs.
void Playfield::hardDrop() {
    if (!mIsGameRunning) {return;}

    mTetrominoManager.move(0, computeMaxDrop()); // perform hard drop

    saveTetrominoToMatrix(); // Save its coordinates to the grid.

    // Award points for landing a Tetromino.
    incrementScoreAndHighScore(Config::pointsTetrominoLanded);

    clearFullLines();
    
    if (isGameOver()) {
        mIsGameRunning = false;
        mIsGameOver = true;
        mOverlayManager.mSetGameOverOverlay = true;
    }

    if (!mIsGameOver) {
        // Prepare the next falling Tetromino.
        mTetrominoManager.setRandomTetromino();
        mTetrominoManager.setInitialLocation();
    }
}

// Checks if there is a collision at an N cells offset on the x axis on the side of the active Tetromino.
// Returns true if there is a collision with a block or the side border of the matrix and false otherwise.
// Ex: n = 1: checks for collision one to the right.
//     n = -1: checks for collision one to the left.
bool Playfield::checkSideCollision(int n) {
    // for all blocks in the active Tetromino.
    for (Tetromino::GridLocation curBlock : mTetrominoManager.mCurShape.blocks) {
        int rowIndex = mTetrominoManager.mCurLocation.y + curBlock.y; // cur row.
        int colIndex = mTetrominoManager.mCurLocation.x + curBlock.x + n; // cell n besides cur column.
        
        // Collision if already touching either side of grid.
        if (colIndex < 0 || colIndex >= Config::playfieldBlockWidth) {
            return true;
        }

        // ensure indices are within valid range.
        if ((0 <= rowIndex && rowIndex < Config::playfieldBlockHeight) &&
            (0 <= colIndex && colIndex < Config::playfieldBlockWidth)) {
            
            if (mMatrix[rowIndex][colIndex] != Config::BlockColor::Empty) {
                return true; // collision with block detected.
            }
        }
    }

    return false; // no collision.
}

// Checks if there is a collision at N cells below the active Tetromino.
// Returns true if there is a collision with a block or the bottom of the matrix
// and false otherwise.
bool Playfield::checkBottomCollision(int n) {
    // for all blocks in the active Tetromino.
    for (Tetromino::GridLocation curBlock : mTetrominoManager.mCurShape.blocks) {
        int rowIndex = mTetrominoManager.mCurLocation.y + curBlock.y + n; // cell n below cur row.
        int colIndex = mTetrominoManager.mCurLocation.x + curBlock.x; // cur column.
        
        // Collision if already touching bottom of grid.
        if (rowIndex >= Config::playfieldBlockHeight) {
            return true;
        }

        // ensure indices are within valid range.
        if ((0 <= rowIndex && rowIndex < Config::playfieldBlockHeight) &&
            (0 <= colIndex && colIndex < Config::playfieldBlockWidth)) {
            
            if (mMatrix[rowIndex][colIndex] != Config::BlockColor::Empty) {
                return true; // collision with block detected.
            }
        }
    }

    return false; // no collision.
}

// Drops the active Tetromino by one cell if no collisions are to occur below.
// Returns true if the drop is successful and false otherwise.
bool Playfield::tryDropOne() {
    // If there is a collision once cell below,
    // we cannot perform the drop.
    if (checkBottomCollision(1)) {
        return false;
    }

    // If no collisions occur for all blocks in the Tetromino,
    // drop the Tetromino by one.
    mTetrominoManager.move(0,1);
    return true;
}

// Based on the location of the active Tetromino, returns the computed
// max amount of cells the active Tetromino is safely allowed to drop without collisions.
// This is used to compute the location for a hard drop or a ghost block.
int Playfield::computeMaxDrop() {
    int count = 0;

    // for all matrix rows below the current location.
    for (int i = mTetrominoManager.mCurLocation.y + 1; i < Config::playfieldBlockHeight; ++i) {
        if (checkBottomCollision(i - mTetrominoManager.mCurLocation.y)) {
            return count;
        }
        ++count;
    }
    return count;
}

// Based on the given shape and location of the active Tetromino,
// Updates the matrix cell values to match the overlaying Tetromino.
void Playfield::saveTetrominoToMatrix() {
    // for all blocks in the active Tetromino.
    for (Tetromino::GridLocation curBlock : mTetrominoManager.mCurShape.blocks) {
        int rowIndex = mTetrominoManager.mCurLocation.y + curBlock.y;
        int colIndex = mTetrominoManager.mCurLocation.x + curBlock.x;
        
        // ensure indices are within valid range.
        if ((0 <= rowIndex && rowIndex < Config::playfieldBlockHeight) &&
            (0 <= colIndex && colIndex < Config::playfieldBlockWidth)) {
            
            // Update color at current matrix location.
            mMatrix[rowIndex][colIndex] = mTetrominoManager.mCurShape.color;
        }
    }
}

// Checks the Matrix for any full rows. If full rows are found, the row is emptied
// and all lines above are shifted down. Points are also awarded for cleared lines.
void Playfield::clearFullLines() {
    // for each line (bottom to top)
    for (int i = Config::playfieldBlockHeight - 1; i >= 0; --i) {
        
        // if line full, award points, clear, and shift down
        if (isLineFull(i)) {
            // Award points
            incrementScoreAndHighScore(Config::pointsLineCleared);
            ++mLinesCleared;

            // shift lines down (clears by overriding).
            shiftLinesDown(i);

            // Increment i so that we can check what used to be the next line
            // but is now in the same location as the one we just cleared.
            ++i;
        }
    }
}

// Performs the setup required to initiate a new game
// and cleanup states of any previous game.
void Playfield::startGame() {
    mScore = 0;
    mLinesCleared = 0;

    flushMatrix();

    // Prepare the first falling Tetromino.
    mTetrominoManager.setRandomTetromino();
    mTetrominoManager.setInitialLocation();
    
    mIsGameOver = false;
    mIsGameRunning = true;
    mIsFirstStart = false;

    mOverlayManager.mSetPauseOverlay = false;
    mOverlayManager.mSetGameOverOverlay = false;

    // Initiate game timer so Tetromino's start to fall.
    Input::TetrisInput::callGameTimer(Config::initialDropSpeedMS);
}

// Checks to see if the top row of the mMatrix contains a block.
// If so returns true that the game is over.
bool Playfield::isGameOver() {
    for (int i = 0; i < Config::playfieldBlockWidth; ++i) {
        if (mMatrix[0][i] != Config::BlockColor::Empty) {
            return true;
        }
    }
    return false;
}

// Upon being called from a timer, makes the active Tetromino
// drop if possible. If not possible, the Tetromino coordinates
// are saved to the matrix and a new active Tetromino is spawned.
void Playfield::onDropTimer(int value) {
    mIsNextDropScheduled = false;

    if (mIsGameRunning) {

        if(!tryDropOne()) {
            // if drop failed. Tetromino has "landed".
            // Save its coordinates to the grid and set a new active Tetromino.
            saveTetrominoToMatrix();

            // Award points for landing a Tetromino.
            incrementScoreAndHighScore(Config::pointsTetrominoLanded);

            // Prepare the next falling Tetromino.
            mTetrominoManager.setRandomTetromino();
            mTetrominoManager.setInitialLocation();
        }

        clearFullLines();

        if (isGameOver()) {
            mIsGameRunning = false;
            mIsGameOver = true;
            mOverlayManager.mSetGameOverOverlay = true;
        }
    }

    // Call Tetromino fall timer again if game is still running
    if (!mIsGameOver) {
        // Increase the drop speed based on the amount of lines the player has cleared.
        int dropSpeed = Config::initialDropSpeedMS - (Config::decreaseDropSpeedPerLineMS * mLinesCleared);
        
        if (dropSpeed < Config::maxDropSpeedCapMS) {
            dropSpeed = Config::maxDropSpeedCapMS;
        }
        
        Input::TetrisInput::callGameTimer(dropSpeed);
    }
}


/// HELPER FUNCTIONS ///

// This function increments the mScore variable while also updating
// mHighScore if the score is greater than the current high score.
// NOTE: mScore should never be incremented directly. It should always
// use this function to ensure the high score remains accurate.
void Playfield::incrementScoreAndHighScore(int amount) {
    mScore += amount;
    if (mScore > mHighScore) {
        mHighScore = mScore;
    }
}

// Sets all the entries of mMatrix to Config::BlockColor::Empty.
void Playfield::flushMatrix() {
    // "zero" initialize the play matrix with empty blocks.
    for (int i = 0; i < Config::playfieldBlockHeight; ++i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            mMatrix[i][j] = Config::BlockColor::Empty;
        }
    }
}

// Returns true if the line at rowIndex in the mMatrix is filled with blocks.
bool Playfield::isLineFull(int rowIndex) {
    int fillCount = 0;

    // check current line to see if full
    for (int i = 0; i < Config::playfieldBlockWidth; ++i) {
        if (mMatrix[rowIndex][i] == Config::BlockColor::Empty) {
            break; // line not full
        }
        ++fillCount;
    }

    // if line full, return true.
    if (fillCount == Config::playfieldBlockWidth) {
        return true;
    }
    return false;
}

// Clears the line at the given row index in the mMatrix
// and shift all lines above it down by one row.
void Playfield::shiftLinesDown(int rowIndex) {
    // shift down existing rows
    for (int i = rowIndex; i > 0; --i) {
        for (int j = 0; j < Config::playfieldBlockWidth; ++j) {
            mMatrix[i][j] = mMatrix[i - 1][j];
        }
    }

    // add a new empty top row
    for (int k = 0; k < Config::playfieldBlockWidth; ++k) {
        mMatrix[0][k] = Config::BlockColor::Empty;
    }
}
