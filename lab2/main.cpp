#include <gl/glut.h>
#include <vector>

#include<iostream>
using namespace std;

std::vector< float > points;

int status=0;

float red=0,green=0,blue=0;
void myMouse(int button, int state, int x, int y)
{

    status= button ==GLUT_LEFT_BUTTON;
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

    glPointSize(5);
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
    int yy;
    cout<<y<<endl;
    yy = glutGet(GLUT_WINDOW_HEIGHT);
    y = yy - y; /* In Glut, Y coordinate increases from top to bottom */
    cout<<yy<<endl;
    if(status )
    {
        points.push_back(x);
        points.push_back(y);
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case '0': red=0;green=0;blue=0;break;
        case '1': red=0;green=199;blue=0;break;
        case '2': red=0;green=0;blue=199;break;
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
