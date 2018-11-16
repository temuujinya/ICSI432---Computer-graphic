#include "GL/freeglut.h"


void renderScene(void) {
    //bg color
    glClearColor(0.2,0.5,0.4,0.5);
    //clear previous  color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,0.0,0.0);
		glVertex3f(0.0,0.5,0.0);
	glEnd();

	glutSwapBuffers();
    //glFlush - use in case when GLUT_SINGLE is used in GLUT_DISPLAY_FUNC. Else if
// GLUT_DOUBLE is used dont necessary to use it.
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    
    //Must include at least 1 argument
    //that is type of buffer i-e SINGLE or DOUBLE buffer.here as I am dealing with the color so I
    //have used GL_RGBA also as I have dealt with these 4 colours.
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300,200);
    glutInitWindowSize(320,320);
    glutCreateWindow("Lighhouse init");

    // register callbacks
    glutDisplayFunc(renderScene);

    //Enter Glut event processing cycle
    glutMainLoop();
    return 1;
}