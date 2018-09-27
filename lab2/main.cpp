#include <GL/glut.h>
#include <vector>

#include<iostream>
using namespace std;

std::vector< float > points;

int status=0,pointSize=5;

float red=0,green=0,blue=0;

void addToPoints(int x, int y){
int yy;
    yy = glutGet(GLUT_WINDOW_HEIGHT);
    y=yy-y;
    if(status){
        points.push_back(x);
        points.push_back(y);
    }
}
void myMouse(int button, int state, int x, int y)
{
  status= button ==GLUT_LEFT_BUTTON;
    addToPoints(x,y);
    glutPostRedisplay();
}

void myDisplay(void)
{
    glClearColor(255.0f, 1.0f, 1.0f, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1080.0, 0.0, 720.0);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glPointSize(pointSize);
    glBegin(GL_POINTS);
    glColor3f(red, green, blue);

for (size_t i = 0; i < points.size(); i += 2)
    {
        glVertex2i( points[i], points[i+1] );
    }
    glEnd();

    glFlush();
}

void moion(int x, int y){
    addToPoints(x,y);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case '0': red=0;green=0;blue=0;break;
        case 'r': red=199;green=0;blue=0;break;
        case 'g': red=0;green=199;blue=0;break;
        case 'b': red=0;green=0;blue=199;break;
        case '2': pointSize=2;break;
        case '3': pointSize=3;break;
        case '4': pointSize=4;break;
        case '5': pointSize=5;break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Draw Pixel");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(moion);
    glutMainLoop();
    return 0;
}
