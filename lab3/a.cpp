#include <GL/glut.h>
#include <iostream>
#include <math.h> 
using namespace std;

#define PI 3.14159265
int width=1000,height=800,CIRCLE_POINTS = 6;

void draw_patter(int view_x, int view_y)
{
	double radius = 100;
    for (double i=2;i<2*radius;i+=2)
    {
        glBegin(GL_LINE_LOOP);
        for (int j=0;j<360;j+=360/CIRCLE_POINTS)
        {
            double angle = (j+i)*PI/180;
            glVertex2f((i) * cos(angle) + radius, i * sin(angle) + radius);
        }
        glEnd();
        glFlush();
    }
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.3f, 1.0f, 1.0f);

    int count = 0;
    for (int i = height; i >= 0; i -= 200){
        for ( int j = 0; j <width; j += 200){
            glViewport(j, i, 200, 200);
            if (count%2 == 0){
                glLoadIdentity();
                gluOrtho2D(0, 200, 0, 200);
                draw_patter(400, 400);
            } else {
                glLoadIdentity();
                gluOrtho2D(200, 0, 0, 200);
                draw_patter(400, 400);
            }
            count++;
        }
    }
}


void resize(int w, int h)
{
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Patern daalgawar");
	glutReshapeFunc(resize);
	glutDisplayFunc(displayMe);

	glutMainLoop();
	return 0;
}
