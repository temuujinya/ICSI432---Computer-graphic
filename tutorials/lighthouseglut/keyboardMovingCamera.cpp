#include <math.h>
#include <GL/freeglut.h>


// angle for rotation for the camera direction
float angle = 0.0;
//actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;


void drawSnowMan(){
	glColor3f(1.0f, 1.0f, 1.0f);
	// Draw body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw head
	glTranslatef(0.0f,1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

	//Draw ground 
	glColor3f(0.9f, 0.9f, 0.9f);

	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
	glColor3f(30.0f, 0.5f, 0.5f);
		glVertex3f(-100.0f, 0.0f,  100.0f);

	glColor3f(0.3f, 30.0f, 0.3f);
		glVertex3f(100.0f, 0.0f,  100.0f);
	glColor3f(0.0f, 0.0f, 30.0f);
		glVertex3f(100.0f, 0.0f,  -100.0f);
	glEnd();
	

	//Draw 36 snowman
	for(int i= -3; i<3; i++){
		for(int j = -3; j<3; j++){
			glPushMatrix();
			glTranslatef(i*10.0,0,j*10.0);
			drawSnowMan();
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 5.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 5.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

    glutSpecialFunc(processSpecialKeys);

	//opengl init
	glEnable(GL_DEPTH_TEST);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
