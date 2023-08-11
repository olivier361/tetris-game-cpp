#include <iostream>
#include <string>
#include "Config.hpp"
#include "TetrisGraphics.hpp"
#include "TetrisInput.hpp"
#include "Playfield.hpp"

// NOTE: This is the entry point for the program.

int main(int argc, char** argv) {
    std::cout << "Welcome to Tetris!\n";
    std::cout << "Please press the 'N' key to start a game.\n";
    std::cout << "More details about the controls can be seen in the graphical window.\n";

    glutInit(&argc, argv);
    Graphics::TetrisGraphics window(Config::windowSizeX, Config::windowSizeY, Config::appName);

    Playfield* gameMatrix = new Playfield(Config::playfieldOriginX, Config::playfieldOriginY);

    Input::TetrisInput inputManager(gameMatrix);

    // Add objects we want rendered to the sDrawableObjectList.
    // NOTE: Pushing into the front ensure the gameMatrix background is drawn
    // first to avoid overriding the blocks that get rendered on top of it.
    window.sDrawableObjectList.push_front(gameMatrix);

    window.displayLoop();
    
    return 0;
}