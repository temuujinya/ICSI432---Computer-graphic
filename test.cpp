#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

#define PI 3.1415926535897932384626433832795

GLint point = 360;
float po=1;

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3);//width of the line default is 1.0
    
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<point;i+=po){
	 float angle;
	 angle= 2*PI*i/point;
	 glVertex2f(cos(angle),sin(angle));
	} 
    glEnd();
    glFlush();      
}
 
void keyboardListen(unsigned char key, int mouseX, int mouseY){
    switch(key){
     case '0':po=1;break;
     case '1':po=36;break;
     case '2':po=180;break;
     case '3':po=120;break;
     case '4':po=90;break;
     case '5':po=72;break;
     case '6':po=60;break;
     case '7':po=51.4285714286;break;
     case '8':po=42;break;
     case '9':po=40;break;
     
    }
    glutPostRedisplay();
}

void specialFuncListen(int key, int x, int y){

    switch(key){
        case GLUT_KEY_UP: po--;break;
        case GLUT_KEY_DOWN: po++;break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    
    glutSpecialFunc(specialFuncListen);    
    glutKeyboardFunc(keyboardListen);
    glutMainLoop();
    return 0;
 
   //glutKeyboardFunc();
}
