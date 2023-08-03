// TODO: Add code here.
// NOTE: This is the entry point for the program.

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>

/// Logic

// std::vector<float> triangle1 = {-0.5, 0.5, 0.5, 0.5, 0.0, -0.5};

class Triangle {
    public:

    std::vector<float> a;
    std::vector<float> b;
    std::vector<float> c;

    Triangle() {
        a = {-0.5, 0.5};
        b = {0.5, 0.5};
        c = {0.0, -0.5};
    }
};

static Triangle triangle1;

// void updateTriangle(Triangle& t) {
//     t.a[1] += 0.00001;
//     t.b[1] += 0.00001;
//     t.c[1] += 0.00001;
// }

void updateTriangle(float x, float y) {
    // triangle1.a[1] -= 0.05;
    // triangle1.b[1] -= 0.05;
    // triangle1.c[1] -= 0.05;

    triangle1.a[0] += x;
    triangle1.b[0] += x;
    triangle1.c[0] += x;

    triangle1.a[1] += y;
    triangle1.b[1] += y;
    triangle1.c[1] += y;
}


// declarations

void display();
void processNormalKeys(unsigned char key, int x, int y);

// definitions

void timer(int) {

    display();

    // re-call for next fame
    glutTimerFunc(1000/60, timer, 0);
}

void set_colour(float r, float g, float b)
{
  float ambient = 0.2f;
  float diffuse = 0.7f;
  float specular = 1.4f;
  GLfloat mat[4];
      /**** set ambient lighting parameters ****/
    mat[0] = ambient*r;
    mat[1] = ambient*g;
    mat[2] = ambient*b;
    mat[3] = 1.0;
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat);

      /**** set diffuse lighting parameters ******/
    mat[0] = diffuse*r;
    mat[1] = diffuse*g;
    mat[2] = diffuse*b;
    mat[3] = 1.0;
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat);

      /**** set specular lighting parameters *****/
    mat[0] = specular*r;
    mat[1] = specular*g;
    mat[2] = specular*b;
    mat[3] = 1.0;
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat);
    glMaterialf (GL_FRONT, GL_SHININESS, 1);
}

void init() {
    // glClearColor(1.0, 1.0, 0.0, 1.0); // R, G, B, A (default pixel color, i.e. background color)
    glClearColor(0.2, 0.3, 1.0, 1.0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Test Window");

    glutDisplayFunc(display);
    // glutTimerFunc(3000, timer, 0); // using glutPostRedisplay() is probably better practice instead
    // glutKeyboardFunc(processNormalKeys);
    init();

    std::cout << "this is a test\n";

    glutKeyboardFunc(processNormalKeys);

    glutMainLoop();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // draw stuff here
    // std::cout << "inside display\n";

    updateTriangle(0.0, -0.0005);

    // does not work
    // set_colour(1.0, 0.0, 0.0); // dark blue

    glColor3f(1.0, 0.0, 0.0);

    // use GL_POLYGON to make a square potentially (or just two triangles)
	glBegin(GL_TRIANGLES);
		// glVertex2d(-0.5, 0.5);
        // glVertex2d(0.5, 0.5);
        // glVertex2d(0.0, -0.5);

        glVertex2d(triangle1.a[0], triangle1.a[1]);
        glVertex2d(triangle1.b[0], triangle1.b[1]);
        glVertex2d(triangle1.c[0], triangle1.c[1]);
	glEnd();

    glRasterPos2i(0, -0.5);
    // glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glColor3f(0.0, 1.0, 0.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Sample Text: 1000");
    
    glFlush();
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
	// if (key == 44 || key == 64) { // D || d
	// 	updateTriangle(0.2, 0.0);
    // }
    // std::cout << "Key pressed\n";
    if (key == 68 || key == 100) { // D || d
		updateTriangle(0.2, 0.0);
    }
}
