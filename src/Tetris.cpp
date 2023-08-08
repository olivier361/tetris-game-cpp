#include <iostream>
#include <string>
#include "Config.hpp"
#include "TetrisGraphics.hpp"
#include "Playfield.hpp"

// NOTE: This is the entry point for the program.

int main(int argc, char** argv) {
    std::cout << "Launching game...\n";

    glutInit(&argc, argv);
    Graphics::TetrisGraphics window(Config::windowSizeX, Config::windowSizeY, Config::appName);

    Playfield* gameMatrix = new Playfield(Config::playfieldOriginX, Config::playfieldOriginY);

    // Add objects we want rendered to the sDrawableObjectList.
    // NOTE: Pushing into the front ensure the gameMatrix background is drawn
    // first to avoid overriding the blocks that get rendered on top of it.
    window.sDrawableObjectList.push_front(gameMatrix);

    window.displayLoop();
    
    // TODO: Delete memory for gameMatrix to avoid memory leaks

    std::cout << "graphics window created!\n";

    // TODO: Implement GlutCloseFunc somewhere. Runs code as the windows is closed with X. Do cleanup steps.
    
    return 0;
}