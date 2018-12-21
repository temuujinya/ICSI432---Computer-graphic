#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#define PI 3.14159265
#include "GL/freeglut.h"  // OpenGL toolkit


using namespace std;

vector<vector<float>> vertex3d;
vector<vector<int>> vertexFace;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

GLfloat cx = 100.0f;
GLfloat cy = 100.0f;
GLfloat cz = 100.0f;

void ReduceToUnit(float *out) {
  float length;

  // Calculate the length of the vector
  length =
      (float)sqrt((out[0] * out[0]) + (out[1] * out[1]) + (out[2] * out[2]));

  // Keep the program from blowing up by providing an exceptable
  // value for outs that may calculated too close to zero.
  if (length == 0.0f) length = 1.0f;

  // Dividing each element by the length will result in a
  // unit normal vector.
  out[0] /= length;
  out[1] /= length;
  out[2] /= length;
}


void calcNormal(const vector<int> &vFace, float *out) {
  float v1[3], v2[3];
  static const int x = 0;
  static const int y = 1;
  static const int z = 2;

  // Calculate two vectors from the three points
  v1[x] = vertex3d[vFace[0] - 1][x] - vertex3d[vFace[1] - 1][x];
  v1[y] = vertex3d[vFace[0] - 1][y] - vertex3d[vFace[1] - 1][y];
  v1[z] = vertex3d[vFace[0] - 1][z] - vertex3d[vFace[1] - 1][z];

  v2[x] = vertex3d[vFace[1] - 1][x] - vertex3d[vFace[2] - 1][x];
  v2[y] = vertex3d[vFace[1] - 1][y] - vertex3d[vFace[2] - 1][y];
  v2[z] = vertex3d[vFace[1] - 1][z] - vertex3d[vFace[2] - 1][z];

  // // Take the cross product of the two vectors to get
  // // the normal vector which will be stored in out
  out[x] = v1[y] * v2[z] - v1[z] * v2[y];
  out[y] = v1[z] * v2[x] - v1[x] * v2[z];
  out[z] = v1[x] * v2[y] - v1[y] * v2[x];

  // Normalize the vector (shorten length to one)
  ReduceToUnit(out);
}


bool is_read = true;

bool ReadFromFile(const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("file!\n");
    return false;
  }
  while (1) {
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) break;  // EOF = End Of File. Quit the loop.}
    if (strcmp(lineHeader, "v") == 0) {
      float x, y, z;
      vector<float> temp;
      fscanf(file, "%f %f %f\n", &x, &y, &z);
      temp.push_back(x);
      temp.push_back(y);
      temp.push_back(z);
      vertex3d.push_back(temp);
    } else if (strcmp(lineHeader, "f") == 0) {
      int x, y, z;
      vector<int> temp;
      fscanf(file, "%d %d %d\n", &x, &y, &z);
      temp.push_back(x);
      temp.push_back(y);
      temp.push_back(z);
      vertexFace.push_back(temp);
    }
  }
}


void renderMat(GLfloat x, GLfloat y,
   GLfloat ambr, GLfloat ambg, GLfloat ambb,
   GLfloat difr, GLfloat difg, GLfloat difb,
   GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine) {
  GLfloat mat[4];

  mat[0] = ambr;
  mat[1] = ambg;
  mat[2] = ambb;
  mat[3] = 1.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
  mat[0] = difr;
  mat[1] = difg;
  mat[2] = difb;
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
  mat[0] = specr;
  mat[1] = specg;
  mat[2] = specb;
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void bunny(){
     glTranslatef(0.5f,-.12f,3.5f);
    float normal[3];
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  gluLookAt(cx, cy, cz, 0, 0, 0, 0, 1, 0);


  GLfloat mat[4];

  renderMat(6.0, 17.0, 0.329412, 0.223529, 0.027451,
      0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843,
      0.21794872);

    glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(200.0f, 0.0f, 1.0f, 0.0f);
  
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < vertexFace.size(); i++) {
    calcNormal(vertexFace[i], normal);
    glNormal3fv(normal);
    // if (i == 0) {
    //     calcNormal(vertexFace[i], normal);
    //     cout << vertex3d[vertexFace[i][0] - 1][0] << " " <<
    //     vertex3d[vertexFace[i][0] - 1][1] << " " << vertex3d[vertexFace[i][0]
    //     - 1][2] << endl; cout << vertex3d[vertexFace[i][1] - 1][0] << " " <<
    //     vertex3d[vertexFace[i][1] - 1][1] << " " << vertex3d[vertexFace[i][1]
    //     - 1][2] << endl; cout << vertex3d[vertexFace[i][2] - 1][0] << " " <<
    //     vertex3d[vertexFace[i][2] - 1][1] << " " << vertex3d[vertexFace[i][2]
    //     - 1][2] << endl;
    // cout << normal[0] << " " << normal[1] << " " << normal[2] << endl;
    // }
    glVertex3f(vertex3d[vertexFace[i][0] - 1][0],
               vertex3d[vertexFace[i][0] - 1][1],
               vertex3d[vertexFace[i][0] - 1][2]);
    glVertex3f(vertex3d[vertexFace[i][1] - 1][0],
               vertex3d[vertexFace[i][1] - 1][1],
               vertex3d[vertexFace[i][1] - 1][2]);
    glVertex3f(vertex3d[vertexFace[i][2] - 1][0],
               vertex3d[vertexFace[i][2] - 1][1],
               vertex3d[vertexFace[i][2] - 1][2]);
  }
  glEnd();

  glPopMatrix();
  glutSwapBuffers();
}


void setup() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(.8f, .6f, 0.3f, 1.0f);
  if (is_read) {
    ReadFromFile("./bunny.obj");
    is_read = false;
  }
//  Light values and coordinates
  GLfloat lightPos[] = {0, 100, 0, 1};
  GLfloat ambientLight[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  // glDepthRange(0.0, 20.0);
  glEnable(GL_DEPTH_TEST);

  // Enable lighting
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);

  // Setup light 0
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specref);

  // Position and turn on the light
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glEnable(GL_LIGHT0);

//   Material
  GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat local_view[] = {0.0};

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
}
// Rotation amounts
// static GLfloat xRot = 0.0f;
// static GLfloat yRot = 0.0f;

////////////////////////////////////////////////////////////////////////////
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h) {
    GLfloat fAspect;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    // gluPerspective(35.0f, fAspect, 1.0, 40.0);
    //glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC() {

    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat     lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);        // Do not calculate inside
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 

    // Black blue background
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}

void chimeglel(GLUquadricObj *pObj, float lX ,float lZ,float lY){
    glPushMatrix();
    // glColor3f(0.0f, 0.0f, 0.0f);

    glColor3ub( rand()%255, rand()%255, rand()%255 );
    
    // glTranslatef(lX,lZ,lY);
    // gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);


    glTranslatef(lX,lZ,lY);
    // glTranslatef(0.1f, -0.12f, 1.0f);
    gluSphere(pObj, 0.2f, 26, 13);
    
    glPopMatrix();
}

void mod(GLUquadricObj *pObj,float lX ,float lZ,float lY){
// glPushMatrix();
//tree body
glColor3f(.0,1.0,.0);
    // glTranslatef(0.1f, -0.12f, 0.0f);
    glTranslatef(lX, lZ, lY);
    glDisable(GL_CULL_FACE);
    gluCylinder(pObj, 2,.0, 3, 26, 1);
   glEnable(GL_CULL_FACE);
 //mod disk

 glDisable(GL_CULL_FACE);
//  glColor3f(1.0f,1.0f,1.0f);
    gluDisk(pObj, 0,2.0f, 26, 13);
glEnable(GL_CULL_FACE);
 

 //tree body2
glColor3f(.0,1.0,.0);
    glTranslatef(0.0f, -0.12f, -2.3f);
    glDisable(GL_CULL_FACE);
    gluCylinder(pObj, 3,.3, 2.6, 26, 1);
   glEnable(GL_CULL_FACE);
 //mod disk

 glDisable(GL_CULL_FACE);
//  glColor3f(1.0f,1.0f,1.0f);
    gluDisk(pObj, 0,3.0f, 26, 13);
glEnable(GL_CULL_FACE);
 


 //tree body3
glColor3f(.0,1.0,.0);
    glTranslatef(0.0f, -0.12f, -2.3f);
    glDisable(GL_CULL_FACE);
    gluCylinder(pObj, 4,.3, 3.0, 26, 1);
   glEnable(GL_CULL_FACE);
 //mod disk

 glDisable(GL_CULL_FACE);
//  glColor3f(1.0f,1.0f,1.0f);
    gluDisk(pObj, 0,4.0f, 26, 13);
glEnable(GL_CULL_FACE);
 


 //tree foot idk
    // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.6,.1,0.2);
    //suliinh ni y dagu + bol deeshee (x,z,y)
    glTranslatef(.0f, .0f, -1.8f);
    glDisable(GL_CULL_FACE);
    gluCylinder(pObj, 1.5, 1.5, 3, 99, 99);
    glEnable(GL_CULL_FACE);

    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.0f, 1.5f, 26, 13);
    glEnable(GL_CULL_FACE);

// glPopMatrix();

    chimeglel(pObj, 1.3f, -.12f, 3.5f);
    chimeglel(pObj, -2.0f, -.12f, 2.5f);
    chimeglel(pObj, -3.4f, -.12f, 1.5f);

}



// Called to draw scene
void RenderScene(void) {
    GLUquadricObj *pObj;  // Quadric Object

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();
    // Move object back and do in place rotation
    glTranslatef(0.0f, -1.0f, -25.0f);
    
    //sum darah bolgond erguuleed baih shig bna
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // Draw something
    pObj = gluNewQuadric();
    gluQuadricTexture(pObj, true);
    gluQuadricNormals(pObj, GLU_SMOOTH);

    //GLU_LINE  GLU_FILL GLU_POINT
    gluQuadricDrawStyle(pObj,GLU_FILL);
    
    // Main Body

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    // glTranslatef(0.0f, 1.17f, 0.0f);
    // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    
    // glDisable(GL_CULL_FACE);
    // gluDisk(pObj, 0.5, 1.3, 32, 32);  // Bottom
    // glEnable(GL_CULL_FACE);
    // glPopMatrix();


    // glPushMatrix();

    // glTranslatef(0.0f, .550f, 0.0f);  // Mid section
    // gluSphere(pObj, .3f, 26, 13);

    // glTranslatef(0.0f, 0.45f, 0.0f);  // Head
    // gluSphere(pObj, 0.24f, 26, 13);
    // glPushMatrix();


/*End mod baih estoi*/

glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
mod(pObj,0.5f,-.12f,3.5f);
bunny();
// mod(pObj,0.5f,-.12f,4.5f);
    // Eyes

    
    
    // chimeglel(pObj);
    // chimeglel(pObj);

    // Nose

glPopMatrix();
    // // Hat
    // glPushMatrix();
    // glColor3f(0.0f, 0.0f, 0.0f);
    // glTranslatef(0.0f, 1.17f, 0.0f);
    // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    // gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);

    // // Hat brim
    // glDisable(GL_CULL_FACE);
    // gluDisk(pObj, 0.17f, 0.28f, 26, 13);
    // glEnable(GL_CULL_FACE);

    // glTranslatef(0.0f, 0.0f, 0.40f);
    // gluDisk(pObj, 0.0f, 0.17f, 26, 13);
    // glPopMatrix();

    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);

glutIdleFunc(RenderScene);
    SetupRC();
    setup();
    glutMainLoop();

    return 0;
}