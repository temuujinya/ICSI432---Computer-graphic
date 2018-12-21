#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#define PI 3.14159265

using namespace std;

vector<vector<float>> vertex3d;
vector<vector<int>> vertexFace;

GLfloat cx = 100.0f;
GLfloat cy = 100.0f;
GLfloat cz = 100.0f;



// XZ position of the camera
float posx=100.0f,posz=100.0f,posy=100.0f;
static float normalx=0, normaly=1, normalz=0;



static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;



void SpecialKeys(int key, int x0, int y0)
    {
    if(key == GLUT_KEY_UP){
        posy = cos(PI/90) * posy - sin(PI/90) * posz;
        posz = cos(PI/90) * posz + sin(PI/90) * posy;
        normaly=cos(PI/90) * normaly - sin(PI/90) * normalz;
        normalz=cos(PI/90) * normalz + sin(PI/90) * normaly;  
        glutPostRedisplay();
    }
    else {if(key == GLUT_KEY_DOWN){
        posy = cos(PI/90) * posy + sin(PI/90) * posz;
        posz = cos(PI/90) * posz - sin(PI/90) * posy;
        normaly=cos(PI/90) * normaly + sin(PI/90) * normalz;
        normalz=cos(PI/90) * normalz - sin(PI/90) * normaly;  
        glutPostRedisplay();
    }
        else{
            if(key==GLUT_KEY_RIGHT){
            posx = cos(PI/90) * posx - sin(PI/90) * posy;
            posy = cos(PI/90) * posy + sin(PI/90) * posx;
            normaly=cos(PI/90) * normaly + sin(PI/90) * normalx;
            normalx=cos(PI/90) * normalx - sin(PI/90) * normaly; 
            glutPostRedisplay();
            }
            else{ if(key == GLUT_KEY_LEFT){
            posx = cos(PI/90) * posx + sin(PI/90) * posy;
            posy = cos(PI/90) * posy - sin(PI/90) * posx;
            normaly=cos(PI/90) * normaly - sin(PI/90) * normalx;
            normalx=cos(PI/90) * normalx + sin(PI/90) * normaly; 
            glutPostRedisplay();
            }
            else{
                if(key == GLUT_KEY_PAGE_UP){
                    float R = sqrt(posx*posx+posy*posy+posz*posz);
                    float Rotz = posz/R;
                    posz = (R - 5)*Rotz;
                    float Roty = posy/R;
                    posy = (R - 5)*Roty;
                    float Rotx = posx/R;
                    posx = (R - 5)*Rotx;
                    glutPostRedisplay();
                    }
                    else{
                        if(key == GLUT_KEY_PAGE_DOWN){
                            float R = sqrt(posx*posx+posy*posy+posz*posz);
                            float Rotz = posz/R;
                            posz = (R + 5)*Rotz;
                            float Roty = posy/R;
                            posy = (R + 5)*Roty;
                            float Rotx = posx/R;
                            posx = (R + 5)*Rotx;
                            glutPostRedisplay();
                        }
                    }
            }
            }
        }
    }

    }


void normalKeyboard(unsigned char key, int x, int y){
  switch(key){
      case ',': 
        posx = cos(PI/90) * posx - sin(PI/90) * posz;
        posz = cos(PI/90) * posz + sin(PI/90) * posx;
        normalx=cos(PI/90) * normalx - sin(PI/90) * normalz;
        normalz=cos(PI/90) * normalz + sin(PI/90) * normalx;  
        glutPostRedisplay();
      break;
      case '.': 
        posx = cos(PI/90) * posx + sin(PI/90) * posz;
        posz = cos(PI/90) * posz - sin(PI/90) * posx;
        normalx=cos(PI/90) * normalx + sin(PI/90) * normalz;
        normalz=cos(PI/90) * normalz - sin(PI/90) * normalx;  
        glutPostRedisplay();
      break;
  }
}


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
    if (res == EOF) break;  // EOF = End Of File
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

void displayMe(void);


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

void displayMe(void) {

  float normal[3];
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  gluLookAt(	posx, posy, posz,
			0, 0, 0,
			normalx, normaly,  normalz);


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

    glVertex3f(vertex3d[vertexFace[i][0]-1][0],
               vertex3d[vertexFace[i][0]-1][1],
               vertex3d[vertexFace[i][0]-1][2]);
    glVertex3f(vertex3d[vertexFace[i][1]-1][0],
               vertex3d[vertexFace[i][1]-1][1],
               vertex3d[vertexFace[i][1]-1][2]);
    glVertex3f(vertex3d[vertexFace[i][2]-1][0],
               vertex3d[vertexFace[i][2]-1][1],
               vertex3d[vertexFace[i][2]-1][2]);
  }
  glEnd();

  glPopMatrix();
  glutSwapBuffers();
}

void resize(int w, int h) {
  GLfloat nRange = 25.0f;
  glViewport(0, 0, w, h);
  GLfloat fAspect = (GLfloat)w / (GLfloat)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(20.0f, fAspect, 1.0, 800.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setup() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(.8f, .6f, 0.3f, 1.0f);

  if (is_read) {
    ReadFromFile("./bunny.obj");
    is_read = false;
  }

//  Light values and coordinates
// x y z ?
  GLfloat lightPos[] = {0, 50, 150, 1};
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

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("bunny obj");
  glutReshapeFunc(resize);
  glutDisplayFunc(displayMe);
  glutSpecialFunc(SpecialKeys);
  glutKeyboardFunc(normalKeyboard);
  setup();
  glutMainLoop();
  return 0;
}