#include "GL/freeglut.h"

void changeSize(int w,int h){
    //цонх хэтэрхий богино үед 0д хуваагдхаас сэргийлж байна.
    //0-н өргөнтэй цон үүсгэж чадахгүй
    if(h==0){
        h=1;
    }

    float ratio = 1.0* w / h;

    //Use the projection matrix
    glMatrixMode(GL_PROJECTION);

    //Reset Matrix
    glLoadIdentity();

    //Set the viewport to be the entire window
    //the first two parameters are the bottom left corner, 
    //and the last two are the width and height of the viewport.
    glViewport(0, 0, w, h);

    //set the correct perspective
    gluPerspective(45, ratio, 1, 1000);
    //Get back to the modelview
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    //bg color
    glClearColor(0.2,0.5,0.4,0.5);
    //clear previous  color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glBegin(GL_TRIANGLES);
        //triagle color
        //just fill in the blanks with RGB values between 0 and 1
		
		glVertex3f(-2,-2,-5.0);
		glVertex3f(2,0.0,-5.0);
		glVertex3f(0.0,2,-5.0);
	glEnd();

    // Using double buffering (GL_DOUBLE in the init function) OpenGL draws in the 
    // back buffer and presents the contents from the front buffer in the window. 
    // When swap buffers is called the buffers are switched, i.e. the previous back 
    // buffer becomes the front buffer showing what was rendered, and the front buffer 
    // becomes the back buffer where the next frame will be rendered.
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

    glutReshapeFunc(changeSize);

    //Enter Glut event processing cycle
    glutMainLoop();
    return 1;
}



/*

Q1: Can you explain the purpose of glutSwapBuffers() 
and more about the Display Modes used in calling the glutInitDisplayMode() function.

A1: Most graphic systems work with double or triple buffering. 
What this means is that there is a buffer being presented on the 
screen, while another is being drawn. At the end of the frame the 
buffers are swapped. That’s why you set GLUT_DOUBLE on the display 
settings. Another setting relates to the type of output, more 
specifically we usually want an RGBA output, i.e. RGB plus alpha. 
The final setting relates to the Z-buffer, aka depth buffer, which 
stores the depths of the pixels currently on the screen, and prevents 
a pixel from being written if its further away than the pixel in the 
frame buffer.
*/