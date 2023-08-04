#include <iostream>
#include <string>
#include "Config.hpp"
#include "TetrisGraphics.hpp"

// NOTE: This is the entry point for the program.

int main(int argc, char** argv) {
    std::cout << "Launching game...\n";

    // TODO: Launch game loop.

    glutInit(&argc, argv);
    Graphics::TetrisGraphics window(Config::windowSizeX, Config::windowSizeY, Config::appName);

    window.displayLoop();
    
    std::cout << "graphics window created!\n";
    
    return 0;
}