#include <cstdio>
#include "TetrisGraphics.hpp"

Graphics::TetrisGraphics::TetrisGraphics(int xSize, int ySize, const char* windowName) {
    
    // Initialize GLUT.
    // glutInit(&argc, argv); // call in main to as arguments need to be passed according to documentation.
    glutInitDisplayMode(GLUT_RGB);

    // Initially open the window with a slight offset from
    // the top left corner of the screen. The user can still
    // move the windows as desired however.
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(xSize, ySize);
    glutCreateWindow(windowName);
}


/// MEMBER FUNCTIONS ///

void Graphics::TetrisGraphics::displayLoop() {
    glutDisplayFunc(displayUpdate);
    glClearColor(0.43, 0.59, 1.0, 1.0); // light pastel blue.
    glutMainLoop();
}


/// STATIC VARIABLE INITIALIZATION ///

std::list<Graphics::DrawableObject *> Graphics::TetrisGraphics::sDrawableObjectList;

int Graphics::TetrisGraphics::timeAtLastFPSMesure;
int Graphics::TetrisGraphics::framesDrawnInLastSecond;
int Graphics::TetrisGraphics::curFPS;

const double Graphics::TetrisGraphics::sColorRed[4] = {1.0, 0.0, 0.0, 1.0};       // #FF0000 Red
const double Graphics::TetrisGraphics::sColorGreen[4] = {0.0, 1.0, 0.0, 1.0};     // #00FF00 Green
const double Graphics::TetrisGraphics::sColorBlue[4] = {0.0, 0.0, 1.0, 1.0};      // #0000FF Blue
const double Graphics::TetrisGraphics::sColorOrange[4] = {1.0, 0.5, 0.0, 1.0};    // #FF7F00 Orange
const double Graphics::TetrisGraphics::sColorPurple[4] = {0.5, 0.0, 0.5, 1.0};    // #800080 Purple
const double Graphics::TetrisGraphics::sColorYellow[4] = {1.0, 1.0, 0.0, 1.0};    // #FFFF00 Yellow
const double Graphics::TetrisGraphics::sColorCyan[4] = {0.0, 1.0, 1.0, 1.0};      // #00FFFF Cyan
const double Graphics::TetrisGraphics::sColorGray[4] = {0.42, 0.42, 0.42, 1.0};   // #6D6D6D Gray

const double Graphics::TetrisGraphics::sColorRedOutline[4] = {0.76, 0.0, 0.0, 1.0};       // #C30000 Dark Red
const double Graphics::TetrisGraphics::sColorGreenOutline[4] = {0.0, 0.76, 0.0, 1.0};     // #00C300 Dark Green
const double Graphics::TetrisGraphics::sColorBlueOutline[4] = {0.0, 0.0, 0.72, 1.0};      // #0000B9 Dark Blue
const double Graphics::TetrisGraphics::sColorOrangeOutline[4] = {0.86, 0.43, 0.0, 1.0};   // #DC6D00 Dark Orange
const double Graphics::TetrisGraphics::sColorPurpleOutline[4] = {0.34, 0.0, 0.34, 1.0};   // #570057 Dark Purple
const double Graphics::TetrisGraphics::sColorYellowOutline[4] = {0.8, 0.8, 0.0, 1.0};     // #CBCB00 Dark Yellow
const double Graphics::TetrisGraphics::sColorCyanOutline[4] = {0.0, 0.68, 0.68, 1.0};     // #00ADAD Dark Cyan
const double Graphics::TetrisGraphics::sColorGrayOutline[4] = {0.25, 0.25, 0.25, 1.0};    // #404040 Dark Gray


/// STATIC FUNCTIONS ///

/// @brief Renders a filled-in square on-screen
///        given the top-left and bottom-right coordinates
///        of the square and the color.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param brx: bottom-right x coordinate.
/// @param bry: bottom-right y coordinate.
/// @param rgba: the color for drawing the square.
void Graphics::TetrisGraphics::drawSquare(double tlx, double tly, double brx, double bry, const double rgba[4]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glBegin(GL_QUADS);
        glVertex2d(tlx, tly);
        glVertex2d(brx, tly);
        glVertex2d(brx, bry);
        glVertex2d(tlx, bry);
    glEnd();
}

/// @brief Renders the outline of a square on-screen
///        given the top-left and bottom-right coordinates
///        of the square, the lineWidth and the color.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param brx: bottom-right x coordinate.
/// @param bry: bottom-right y coordinate.
/// @param lineWidth: the width in pixels of the outline.
/// @param rgba: the color for drawing the square.
void Graphics::TetrisGraphics::drawSquareOutline(double tlx, double tly, double brx, double bry, double lineWidth, const double rgba[4]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
        glVertex2d(tlx, tly);
        glVertex2d(brx, tly);
        glVertex2d(brx, bry);
        glVertex2d(tlx, bry);
    glEnd();
}

/// @brief Renders a Tetris block of the given Config::BlockColor
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param blockColor: the Config::BlockColor for drawing the block.
void Graphics::TetrisGraphics::drawBlock(double tlx, double tly, const Config::BlockColor blockColor) {
    const int outlineWidth = 3;
    const double (*pPrimaryColor)[4];
    const double (*pOutlineColor)[4];

    // Select correct RGBA values to draw based on blockColor parameter.
    switch (blockColor) {
        case Config::BlockColor::Red:
            pPrimaryColor = &sColorRed;
            pOutlineColor = &sColorRedOutline;
            break;
        case Config::BlockColor::Green:
            pPrimaryColor = &sColorGreen;
            pOutlineColor = &sColorGreenOutline;
            break;
        case Config::BlockColor::Blue:
            pPrimaryColor = &sColorBlue;
            pOutlineColor = &sColorBlueOutline;
            break;
        case Config::BlockColor::Orange:
            pPrimaryColor = &sColorOrange;
            pOutlineColor = &sColorOrangeOutline;
            break;
        case Config::BlockColor::Purple:
            pPrimaryColor = &sColorPurple;
            pOutlineColor = &sColorPurpleOutline;
            break;
        case Config::BlockColor::Yellow:
            pPrimaryColor = &sColorYellow;
            pOutlineColor = &sColorYellowOutline;
            break;
        case Config::BlockColor::Cyan:
            pPrimaryColor = &sColorCyan;
            pOutlineColor = &sColorCyanOutline;
            break;
        case Config::BlockColor::Gray:
            pPrimaryColor = &sColorGray;
            pOutlineColor = &sColorGrayOutline;
            break;
        case Config::BlockColor::Empty:
        default:
            return; // nothing to draw for empty block.
    }

    // draw the block with the chosen color.
    drawSquare(tlx, tly, tlx + Config::blockSizePx, tly + Config::blockSizePx, *pOutlineColor); // draw outline.
    drawSquare(tlx + outlineWidth, tly + outlineWidth,
        tlx - outlineWidth + Config::blockSizePx, tly - outlineWidth + Config::blockSizePx, *pPrimaryColor); // draw inside block.
}

/// @brief Displays the given string on-screen with the Helvetica 18 text being
///        left justified starting at the given coordinates.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param rgba: the color for drawing the text. 
/// @param text: the string to render.
void Graphics::TetrisGraphics::drawText(double tlx, double tly, const double rgba[4], const char text[]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glRasterPos2d(tlx, tly);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);
}

/// @brief Displays the given string on-screen with the Times Roman 24 text being
///        left justified starting at the given coordinates.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param rgba: the color for drawing the text. 
/// @param text: the string to render.
void Graphics::TetrisGraphics::drawHeader(double tlx, double tly, const double rgba[4], const char text[]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glRasterPos2d(tlx, tly);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text);
}

/// HELPER FUNCTIONS ///

void Graphics::TetrisGraphics::displayUpdate() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // This makes sets the viewport to be of a fixed size no matter
    // if the window shape is rezised by the user.
    // Doing so avoids rendered shapes to be squished/stretched when
    // changing the window's aspect ratio.
    glViewport(0, 0, Config::windowSizeX, Config::windowSizeY);

    // Transforms the coordinates used to render shapes from relative coordinates
    // (-1.0 <= x <= 1.0, -1.0 <= y <= 1.0) to using exact pixel coordinates
    // (0 <= x <= 1279, 0 <= y <= 719).
    glOrtho(0.0, Config::windowSizeX, Config::windowSizeY, 0.0, 0.0, 1.0);

    // draw stuff here
    // std::cout << "inside display\n";

    // updateTriangle(0.0, -0.0005);

    // does not work
    // set_colour(1.0, 0.0, 0.0); // dark blue

    // glColor3f(1.0, 0.0, 0.0);

    // // use GL_POLYGON to make a square potentially (or just two triangles)
	// glBegin(GL_TRIANGLES);
	// 	// glVertex2d(-0.5, 0.5);
    //     // glVertex2d(0.5, 0.5);
    //     // glVertex2d(0.0, -0.5);

    //     glVertex2d(-0.5, 0.5);
    //     glVertex2d(0.5, 0.5);
    //     glVertex2d(0.0, -0.5);
	// glEnd();

    // Call the display function of each registered DrawableObject.

    // TODO: Remove vector implementation
    // for (std::size_t i = 0; i < sDrawableObjectList.size(); ++i) {
    //     sDrawableObjectList[i]->display();
    // }
    // list implementation
    for (auto iter = sDrawableObjectList.begin(); iter != sDrawableObjectList.end(); ++iter) {
        (*iter)->display();
    }
    
    glColor3f(0.0, 1.0, 0.0);
    // glRasterPos2i(0, -0.5);
    glRasterPos2d(0.0, -0.5);
    // glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Sample Text: 1000");
    

    // Compute and display framerate:

    if (Config::displayFPS) {
        ++framesDrawnInLastSecond;

        int timeSinceBoot = glutGet(GLUT_ELAPSED_TIME);

        // compute average fps in the last second of runtime.
        if (timeSinceBoot - timeAtLastFPSMesure >= 1000) {
            curFPS = (int) (framesDrawnInLastSecond * (1000.0 / (double)(timeSinceBoot - timeAtLastFPSMesure)));
            framesDrawnInLastSecond = 0;
            timeAtLastFPSMesure = timeSinceBoot;
        }

        // display the FPS string on-screen.
        char fpsString[128];
        sprintf(fpsString,"AVG FPS: %4d", curFPS);

        glColor3f(0.0, 0.0, 1.0);
        glRasterPos2d(10, Config::windowSizeY - 10);
        glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)fpsString);
    }

    // flush buffer to and call function again to render next frame.
    glFlush();
    glutPostRedisplay();
}



