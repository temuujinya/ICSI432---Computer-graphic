#include <GL/glut.h>
#include <vector>

#include<iostream>
using namespace std;


int status=0,pointSize=5;
float red=255,green=255,blue=255;

void addToPoints(int x, int y){
int yy = glutGet(GLUT_WINDOW_HEIGHT);
    y=yy-y;
    if(status){    
        glColor3f(red, green, blue);
        glPointSize(pointSize);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
    glFlush();
    }
}


// void myDisplay(void)
// {
//     // glLoadIdentity();
//     // gluOrtho2D(0.0, 1080.0, 0.0, 720.0);
// }

void resize(GLint width, GLint height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glViewport(0, 0, width, height); 

    gluOrtho2D(0, width, 0.0, height);
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void moion(int x, int y){
    addToPoints(x,y);
    // glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
  status= button ==GLUT_LEFT_BUTTON;
    addToPoints(x,y);
    // glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        // case '0': glClear();break;
        case 'w': red=255;green=255;blue=255;break;
        case 'r': red=199;green=0;blue=0;break;
        case 'g': red=0;green=199;blue=0;break;
        case 'b': red=0;green=0;blue=199;break;
        case '2': pointSize=2;break;
        case '3': pointSize=3;break;
        case '4': pointSize=4;break;
        case '5': pointSize=5;break;
        case '9': pointSize=10;break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Black board");
    // glutDisplayFunc(myDisplay);
    glutReshapeFunc(resize);
    glutMotionFunc(moion);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
