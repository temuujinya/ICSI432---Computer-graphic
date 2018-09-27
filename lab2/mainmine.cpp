#include<GL/glut.h>
#include<iostream>
#include<math.h>
using namespace std;

float pointpos[100];
float po =1, nowX=0,nowY=0;

void displayMe(){
    glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(1,1,1,0);
    /*
    draw polygon(square) of unit legth centered at the origin 
    this code draws each vertex int different color
    */
    glBegin(GL_POINTS);
        // glColor3f(1.0,0.0,0.0);
        glVertex2f(nowX,nowY);
    glEnd();   
    glutPostRedisplay();
}

int clicking =0;
void mouseListen(int button, int state, int x, int y){
    if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN){
            clicking=state == GLUT_DOWN;
            cout<<"MOUSE RIGHT DOWN"<<endl;
        }
    }
    glFlush();
}

void motionListen(int x, int y){
    if(clicking){
        nowX=x;
        nowY=y;
        cout<<"motion x="<<x<<" y="<<y<<endl;
        // glColor3f(1.0,0,0);
        // glBegin(GL_POINTS);
        // glVertex2i(x,y);
        // glEnd();
    }
    // glFlush();
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMouseFunc(mouseListen);
    glutMotionFunc(motionListen);
    gluOrtho2D(0.0,640.0,0.0,480.0);
    glutMainLoop();
    return 0;
}