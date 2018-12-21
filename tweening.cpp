#include "GL/freeglut.h"
int t = 0.0;
// //Initial square position and size
// GLfloat x1=100.0f;
// GLfloat y1=150.0f;
// GLsizei rsize=50;

// //Step size in x and y directions
// GLfloat xstep=1.0f;
// GLfloat ystep=1.0f;

// GLfloat winWidth, winHeight;

// void changeSize(int w,int h){
//     //цонх хэтэрхий богино үед 0д хуваагдхаас сэргийлж байна.
//     //0-н өргөнтэй цон үүсгэж чадахгүй
//     if(h==0){
//         h=1;
//     }

//     float ratio = 1.0* w / h;

//     //Use the projection matrix
//     glMatrixMode(GL_PROJECTION);

//     //Reset Matrix
//     glLoadIdentity();

//     //Set the viewport to be the entire window
//     //the first two parameters are the bottom left corner, 
//     //and the last two are the width and height of the viewport.
//     glViewport(0, 0, w, h);

//     //set the correct perspective
//     gluPerspective(45, ratio, 1, 1000);
//     //Get back to the modelview
//     glMatrixMode(GL_MODELVIEW);
// }


 void timer(int value) {
//     if (x1>winWidth-rsize || x1<0)
//         xstep=-xstep;
//     if (y1>winHeight-rsize || y1<0)
//         ystep=-ystep;
//     if (x1>winWidth-rsize)
//         x1=winWidth-rsize-1;
//      if (y1>winHeight-rsize)
//         y1=winHeight-rsize-1;
//     x1+=xstep;
//     y1+=ystep;

t+=0.1;
     glutPostRedisplay();
     glutTimerFunc(3, timer, 1);
 }


void renderScene(){

    glClearColor(0.2,0.5,0.4,0.5);



    // // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // //reset transformations
    // glLoadIdentity();
    // // //set the camera 
    // gluLookAt(  0.0f,0.0f,0.0f,
    //             0.0f, 0.0f, 0.0f,
    //             0.0f, 1.0f, 0.0f);

    //glRotatef(0, 0.0f,1.0f,0.0f);



        glColor3f(0.5,0.5,1);
	glBegin(GL_TRIANGLES);
        //triagle color
        //just fill in the blanks with RGB values between 0 and 1
	
        glColor3f(0.5,0.5,1);
		//glVertex2f(.1,.3);
		glVertex2f((1-t)*.1+0.9*t, (1-t)*.3+0.9*t);

        glColor3f(0.3,0.3,0);		
		//glVertex2f(.10,.15);
		glVertex2f((1-t)*.10+0.18*t, (1-t)*.15+0.21*t);

        glColor3f(0.3,0.2,.9);
		//glVertex2f(.20,.25);
		glVertex2f((1-t)*.20+0.8*t, (1-t)*.25+0.31*t);
	glEnd();

    glFlush();
    //glutPostRedisplay();

}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    
    //Must include at least 1 argument
    //that is type of buffer i-e SINGLE or DOUBLE buffer.here as I am dealing with the color so I
    //have used GL_RGBA also as I have dealt with these 4 colours.
    // glutInitDisplayMode(/*GLUT_DEPTH | GLUT_DOUBLE | */GLUT_SINGLE|GLUT_RGBA);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    
    glutInitWindowPosition(300,200);
    glutInitWindowSize(1080,720);
    glutCreateWindow("Lighhouse init");

    // register callbacks
    glutDisplayFunc(renderScene);
    // glutReshapeFunc(changeSize);
    glutTimerFunc(3, timer, 1);

    // here is th eidke func registration
    // glutIdleFunc(renderScene);

    //Enter Glut event processing cycle
    glutMainLoop();
    return 1;
}
