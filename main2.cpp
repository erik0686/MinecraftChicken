/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
/* Global variables */
char title[] = "3D Shapes";

double translateA = 0.0, translateB = 0.0, translateC = -9.0;
double rotateA = 25.0, rotateB = 0.9, rotateC = -1.5, rotateD = 0.0;
double scaleA = 1, scaleB = 1, scaleC = 1;
//gcc main2.cpp -o main3 -lGL -lGLU -lglut

unsigned char CHECKERS [4][4]={{000,255,000,255},
                               {255,000,255,000},
                               {000,255,000,255},
                               {255,000,255,000}
};

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

void makeCheckImage(void)
{
   int i, j, c;

    //Generating Checker Patterm
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

   makeCheckImage();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                checkImage);
   // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void displayEjes(){
  glBegin(GL_LINES);
  // EJES

   // draw line for x axis
   glColor3f(5.0, 0.0, 0.0); //rojo
   glVertex3f(0.0, 0.0, 0.0);
   glVertex3f(5.0, 0.0, 0.0);
   // draw line for y axis
   glColor3f(0.0, 5.0, 0.0); //green
   glVertex3f(0.0, 0.0, 0.0);
   glVertex3f(0.0, 5.0, 0.0);
   // draw line for Z axis
   glColor3f(0.0, 0.0, 5.0); //blue
   glVertex3f(0.0, 0.0, 0.0);
   glVertex3f(0.0, 0.0, 5.0);
  glEnd();
}

void displayPatas(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // PATAS

  // Back face (z = -0.5f)
  // glColor3f(1.0f, 1.0f, 0.0f);     // Rosa izquierda
  glTexCoord2f(0, 0);glVertex3f( 0.3f,  0.0f, 0.3f);
  glTexCoord2f(0, 1);glVertex3f( 0.1f,  0.0f, 0.3f);
  glTexCoord2f(1, 1);glVertex3f( 0.1f, -0.7f, 0.3f);
  glTexCoord2f(1, 0);glVertex3f( 0.3f, -0.7f, 0.3f);

  // glColor3f(1.0f, 1.0f, 0.0f);     // Rosa izquierda
  glTexCoord2f(0, 0);glVertex3f( 0.8f,  0.0f, 0.3f);
  glTexCoord2f(0, 1);glVertex3f( 0.6f,  0.0f, 0.3f);
  glTexCoord2f(1, 1);glVertex3f( 0.6f, -0.7f, 0.3f);
  glTexCoord2f(1, 0);glVertex3f( 0.8f, -0.7f, 0.3f);

  // glColor3f(1.0f, 1.0f, 0.0f);     // Green
  glTexCoord2f(0, 0);glVertex3f( 0.85f, -0.7f, 0.2f);
  glTexCoord2f(0, 1);glVertex3f( 0.55f, -0.7f, 0.2f);
  glTexCoord2f(1, 1);glVertex3f( 0.55f, -0.7f, 0.8f);
  glTexCoord2f(1, 0);glVertex3f( 0.85f, -0.7f, 0.8f);

  // glColor3f(1.0f, 1.0f, 0.0f);     // Green
  glTexCoord2f(0, 0);glVertex3f( 0.35f, -0.7f, 0.2f);
  glTexCoord2f(0, 1);glVertex3f( 0.05f, -0.7f, 0.2f);
  glTexCoord2f(1, 1);glVertex3f( 0.05f, -0.7f, 0.8f);
  glTexCoord2f(1, 0);glVertex3f( 0.35f, -0.7f, 0.8f);


  glEnd();  // End of drawing color-cube

  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

void displayCuerpo(){
  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // CUERPO
   // top face
    // glColor3f(0.5f, 0.5f, 0.5f);     // Green

    glTexCoord2f(0, 0);glVertex3f( 1.0f, 1.0f, -0.3f);
    glTexCoord2f(0, 2);glVertex3f(-0.0f, 1.0f, -0.3f);
    glTexCoord2f(2, 2);glVertex3f(-0.0f, 1.0f,  1.3f);
    glTexCoord2f(2, 0);glVertex3f( 1.0f, 1.0f,  1.3f);

    // Bottom face (y = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 1.0f, -0.0f,  1.3f);
    glTexCoord2f(0, 2);glVertex3f(-0.0f, -0.0f,  1.3f);
    glTexCoord2f(2, 2);glVertex3f(-0.0f, -0.0f, -0.3f);
    glTexCoord2f(2, 0);glVertex3f( 1.0f, -0.0f, -0.3f);
    //
    // front face  (z = 0.5f)
    // glColor3f(0.5f, 0.5f, 1.0f);     // Rosa izquierda
    glTexCoord2f(0, 0);glVertex3f( 1.0f,  1.0f, 1.3f);
    glTexCoord2f(0, 2);glVertex3f(-0.0f,  1.0f, 1.3f);
    glTexCoord2f(2, 2);glVertex3f(-0.0f, -0.0f, 1.3f);
    glTexCoord2f(2, 0);glVertex3f( 1.0f, -0.0f, 1.3f);

    // Back face (z = -0.5f)
    // glColor3f(1.0f, 1.5f, 0.5f);     // Yellow
    glTexCoord2f(0, 0);glVertex3f( 1.0f, -0.0f, -0.3f);
    glTexCoord2f(0, 2);glVertex3f(-0.0f, -0.0f, -0.3f);
    glTexCoord2f(2, 2);glVertex3f(-0.0f,  1.0f, -0.3f);
    glTexCoord2f(2, 0);glVertex3f( 1.0f,  1.0f, -0.3f);
    //
    // Left face (x = -0.5f)
    // glColor3f(1.0f, 0.5f, 0.5f);     // rosa
    glTexCoord2f(0, 0);glVertex3f(0.0f,  1.0f,  1.3f);
    glTexCoord2f(0, 2);glVertex3f(0.0f,  1.0f, -0.3f);
    glTexCoord2f(2, 2);glVertex3f(0.0f, -0.0f, -0.3f);
    glTexCoord2f(2, 0);glVertex3f(0.0f, -0.0f,  1.3f);
    //
    // Right face (x = 0.5f)
    // glColor3f(1.0f, 0.5f, 0.5f);     // Magenta
    glTexCoord2f(0, 0);glVertex3f(1.0f,  1.0f, -0.3f);
    glTexCoord2f(0, 2);glVertex3f(1.0f,  1.0f,  1.3f);
    glTexCoord2f(2, 2);glVertex3f(1.0f, -0.0f,  1.3f);
    glTexCoord2f(2, 0);glVertex3f(1.0f, -0.0f, -0.3f);

  glEnd();  // End of drawing color-cube

    GLUquadricObj *quadric;
    quadric=gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricOrientation(quadric,GLU_INSIDE);

    // Render
    glPushMatrix();
    glTranslated(0,0,-3);
    // gluSphere(quadric,1,16,16);
    //// gluCylinder (or cone),gluDisk,gluPartialDisk

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void displayAlaIzq(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // ALAS
   // top face
    // glColor3f(0.5f, 0.5f, 0.5f);     // Green
    glTexCoord2f(0, 0);glVertex3f( 0.0f, 1.0f, -0.0f);
    glTexCoord2f(0, 5);glVertex3f(-0.3f, 1.0f, -0.0f);
    glTexCoord2f(5, 5);glVertex3f(-0.3f, 1.0f,  1.0f);
    glTexCoord2f(5, 0);glVertex3f( 0.0f, 1.0f,  1.0f);

    // Bottom face (y = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 0.0f, 0.3f,  1.0f);
    glTexCoord2f(0, 5);glVertex3f(-0.3f, 0.3f,  1.0f);
    glTexCoord2f(5, 5);glVertex3f(-0.3f, 0.3f, -0.0f);
    glTexCoord2f(5, 0);glVertex3f( 0.0f, 0.3f, -0.0f);
    //
    // front face  (z = 0.5f)
    // glColor3f(0.5f, 0.5f, 1.0f);     // Rosa izquierda
    glTexCoord2f(0, 0);glVertex3f( 0.0f,  1.0f, 1.0f);
    glTexCoord2f(0, 5);glVertex3f(-0.3f,  1.0f, 1.0f);
    glTexCoord2f(5, 5);glVertex3f(-0.3f, 0.3f, 1.0f);
    glTexCoord2f(5, 0);glVertex3f( 0.0f, 0.3f, 1.0f);

    // Back face (z = -0.5f)
    // glColor3f(1.0f, 1.5f, 0.5f);     // Yellow
    glTexCoord2f(0, 0);glVertex3f( 0.0f, 0.3f, -0.0f);
    glTexCoord2f(0, 5);glVertex3f(-0.3f, 0.3f, -0.0f);
    glTexCoord2f(5, 5);glVertex3f(-0.3f,  1.0f, -0.0f);
    glTexCoord2f(5, 0);glVertex3f( 0.0f,  1.0f, -0.0f);
    //
    // Left face (x = -0.5f)
    // glColor3f(1.0f, 0.5f, 0.5f);     // rosa
    glTexCoord2f(0, 0);glVertex3f(-0.3f,  1.0f,  1.0f);
    glTexCoord2f(0, 5);glVertex3f(-0.3f,  1.0f, -0.0f);
    glTexCoord2f(5, 5);glVertex3f(-0.3f, 0.3f, -0.0f);
    glTexCoord2f(5, 0);glVertex3f(-0.3f, 0.3f,  1.0f);
    //
    // Right face (x = 0.5f)
    // glColor3f(1.0f, 0.3f, 0.8f);     // Magenta
    glTexCoord2f(0, 0);glVertex3f(0.0f,  1.0f, -0.0f);
    glTexCoord2f(0, 5);glVertex3f(0.0f,  1.0f,  1.0f);
    glTexCoord2f(5, 5);glVertex3f(0.0f, 0.3f,  1.0f);
    glTexCoord2f(5, 0);glVertex3f(0.0f, 0.3f, -0.0f);
  glEnd();  // End of drawing color-cube

  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

void displayAlaDer(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // ALAS
   // top face
    // glColor3f(0.5f, 0.5f, 0.5f);     // Green
    glTexCoord2f(0, 0);glVertex3f( 1.3f, 1.0f, -0.0f);
    glTexCoord2f(0, 5);glVertex3f(1.0f, 1.0f, -0.0f);
    glTexCoord2f(5, 5);glVertex3f(1.0f, 1.0f,  1.0f);
    glTexCoord2f(5, 0);glVertex3f( 1.3f, 1.0f,  1.0f);

    // Bottom face (y = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 1.3f, 0.3f,  1.0f);
    glTexCoord2f(0, 5);glVertex3f(1.0f, 0.3f,  1.0f);
    glTexCoord2f(5, 5);glVertex3f(1.0f, 0.3f, -0.0f);
    glTexCoord2f(5, 0);glVertex3f( 1.3f, 0.3f, -0.0f);
    //
    // front face  (z = 0.5f)
    // glColor3f(0.5f, 0.5f, 1.0f);     // Rosa izquierda
    glTexCoord2f(0, 0);glVertex3f( 1.3f,  1.0f, 1.0f);
    glTexCoord2f(0, 5);glVertex3f(1.0f,  1.0f, 1.0f);
    glTexCoord2f(5, 5);glVertex3f(1.0f, 0.3f, 1.0f);
    glTexCoord2f(5, 0);glVertex3f( 1.3f, 0.3f, 1.0f);

    // Back face (z = -0.5f)
    // glColor3f(1.0f, 1.5f, 0.5f);     // Yellow
    glTexCoord2f(0, 0);glVertex3f( 1.3f, 0.3f, -0.0f);
    glTexCoord2f(0, 5);glVertex3f(1.0f, 0.3f, -0.0f);
    glTexCoord2f(5, 5);glVertex3f(1.0f,  1.0f, -0.0f);
    glTexCoord2f(5, 0);glVertex3f( 1.3f,  1.0f, -0.0f);
    //
    // Left face (x = -0.5f)
    // glColor3f(1.0f, 0.5f, 0.5f);     // rosa
    glTexCoord2f(0, 0);glVertex3f(1.0f,  1.0f,  1.0f);
    glTexCoord2f(0, 5);glVertex3f(1.0f,  1.0f, -0.0f);
    glTexCoord2f(5, 5);glVertex3f(1.0f, 0.3f, -0.0f);
    glTexCoord2f(5, 0);glVertex3f(1.0f, 0.3f,  1.0f);
    //
    // Right face (x = 0.5f)
    // glColor3f(1.0f, 0.3f, 0.8f);     // Magenta
    glTexCoord2f(0, 0);glVertex3f(1.3f,  1.0f, -0.0f);
    glTexCoord2f(0, 5);glVertex3f(1.3f,  1.0f,  1.0f);
    glTexCoord2f(5, 5);glVertex3f(1.3f, 0.3f,  1.0f);
    glTexCoord2f(5, 0);glVertex3f(1.3f, 0.3f, -0.0f);
  glEnd();  // End of drawing color-cube
  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

void displayCabeza(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // CABEZA


    // Bottom face (y = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 0.7f, 0.5f, 0.2f);
    glTexCoord2f(0, 3.5);glVertex3f( 0.1f, 0.5f, 0.2f);
    glTexCoord2f(3.5, 3.5);glVertex3f( 0.1f, 0.5f, 1.2f);
    glTexCoord2f(3.5, 0);glVertex3f( 0.7f, 0.5f, 1.2f);
    // //
    // Back face (z = -0.5f)
    // glColor3f(0.5f, 0.5f, 0.5f);     // Rosa izquierda
    glTexCoord2f(0, 0);glVertex3f( 0.7f,  1.3f, 0.2f);
    glTexCoord2f(0, 3.5);glVertex3f( 0.1f,  1.3f, 0.2f);
    glTexCoord2f(3.5, 3.5);glVertex3f( 0.1f, 0.5f, 0.2f);
    glTexCoord2f(3.5, 0);glVertex3f( 0.7f, 0.5f, 0.2f);
    // //
    // Left face (x = -0.5f)
    // glColor3f(0.0f, 0.3f, 0.8f);     // Magenta
    glTexCoord2f(0, 0);glVertex3f(0.1f, 1.3f, 0.2f);
    glTexCoord2f(0, 3.5);glVertex3f(0.1f, 1.3f, 1.2f);
    glTexCoord2f(3.5, 3.5);glVertex3f(0.1f, 0.5f, 1.2f);
    glTexCoord2f(3.5, 0);glVertex3f(0.1f, 0.5f, 0.2f);
    // //
    // Right face (x = 0.5f)
    // glColor3f(0.0f, 0.3f, 0.8f);     // Magenta
    glTexCoord2f(0, 0);glVertex3f(0.7f, 1.3f, 0.2f);
    glTexCoord2f(0, 3.5);glVertex3f(0.7f, 1.3f, 1.2f);
    glTexCoord2f(3.5, 3.5);glVertex3f(0.7f, 0.5f, 1.2f);
    glTexCoord2f(3.5, 0);glVertex3f(0.7f, 0.5f, 0.2f);

    // top face
     // glColor3f(0.2f, 0.2f, 0.2f);     // Green
     glTexCoord2f(0, 0);glVertex3f( 0.7f, 1.3f, 0.2f);
     glTexCoord2f(0, 3.5);glVertex3f( 0.1f, 1.3f, 0.2f);
     glTexCoord2f(3.5, 3.5);glVertex3f( 0.1f, 1.3f, 1.2f);
     glTexCoord2f(3.5, 0);glVertex3f( 0.7f, 1.3f, 1.2f);

    // front face  (z = 0.5f)
    // glColor3f(0.2f, 0.2f, 0.2f);     // Rosa izquierda
    glTexCoord2f(0, 0);glVertex3f( 0.7f,  1.3f, 1.2f);
    glTexCoord2f(0, 3.5);glVertex3f( 0.1f,  1.3f, 1.2f);
    glTexCoord2f(3.5, 3.5);glVertex3f( 0.1f, 0.5f, 1.2f);
    glTexCoord2f(3.5, 0);glVertex3f( 0.7f, 0.5f, 1.2f);
    //
  glEnd();  // End of drawing color-cube
  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

void displayPico(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // PICO


    // Bottom face (y = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 0.7f, 0.8f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f( 0.1f, 0.8f, 1.2f);
    glTexCoord2f(.5, .5);glVertex3f( 0.1f, 0.8f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f( 0.7f, 0.8f, 1.4f);
    // //
    //Back face (z = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 0.7f,  1.0f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f( 0.1f,  1.0f, 1.2f);
    glTexCoord2f(.5, .5);glVertex3f( 0.1f, 0.8f, 1.2f);
    glTexCoord2f(.5, 0);glVertex3f( 0.7f, 0.8f, 1.2f);
    // //
    // // Left face (x = -0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f(0.1f, 0.8f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f(0.1f, 1.0f, 1.2f);//
    glTexCoord2f(.5, .5);glVertex3f(0.1f, 0.8f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f(0.1f, 1.0f, 1.4f);
    // //
    // // Right face (x = 0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f(0.7f, 0.8f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f(0.7f, 1.0f, 1.2f);//
    glTexCoord2f(.5, .5);glVertex3f(0.7f, 0.8f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f(0.7f, 1.0f, 1.4f);
    //
    // top face
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 0.7f, 1.0f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f( 0.1f, 1.0f, 1.2f);
    glTexCoord2f(.5, .5);glVertex3f( 0.1f, 1.0f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f( 0.7f, 1.0f, 1.4f);

    // // front face  (z = 0.5f)
    // glColor3f(1.0f, 1.0f, 0.5f);
    glTexCoord2f(0, 0);glVertex3f( 0.7f,  1.0f, 1.4f);
    glTexCoord2f(0, .5);glVertex3f( 0.1f,  1.0f, 1.4f);
    glTexCoord2f(.5, .5);glVertex3f( 0.1f, 0.8f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f( 0.7f, 0.8f, 1.4f);

  glEnd();  // End of drawing color-cube
  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

void displayOjos(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads


  // glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0, 0);glVertex3f( 0.4f,  1.2f, 1.4f);
  glTexCoord2f(0, .5);glVertex3f( 0.2f,  1.2f, 1.4f);
  glTexCoord2f(.5, .5);glVertex3f( 0.2f, 1.0f, 1.4f);
  glTexCoord2f(.5, 0);glVertex3f( 0.4f, 1.0f, 1.4f);

  // glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0, 0);glVertex3f( 0.7f,  1.2f, 1.4f);
  glTexCoord2f(0, .5);glVertex3f( 0.5f,  1.2f, 1.4f);
  glTexCoord2f(.5, .5);glVertex3f( 0.5f, 1.0f, 1.4f);
  glTexCoord2f(.5, 0);glVertex3f( 0.7f, 1.0f, 1.4f);

  glEnd();
  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void displayPapada(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads

    // Bottom face (y = -0.5f)
    // glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);glVertex3f( 0.5f, 0.6f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f( 0.3f, 0.6f, 1.2f);
    glTexCoord2f(.5, .5);glVertex3f( 0.3f, 0.6f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f( 0.5f, 0.6f, 1.4f);
    // //
    //Back face (z = -0.5f)
    // glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);glVertex3f( 0.5f,  0.8f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f( 0.3f,  0.8f, 1.2f);
    glTexCoord2f(.5, .5);glVertex3f( 0.3f, 0.6f, 1.2f);
    glTexCoord2f(.5, 0);glVertex3f( 0.5f, 0.6f, 1.2f);
    // //
    // // Left face (x = -0.5f)
    // glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);glVertex3f(0.3f, 0.6f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f(0.3f, 0.8f, 1.2f);//
    glTexCoord2f(.5, .5);glVertex3f(0.3f, 0.6f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f(0.3f, 0.8f, 1.4f);
    // //
    // // Right face (x = 0.5f)
    // glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);glVertex3f(0.5f, 0.6f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f(0.5f, 0.8f, 1.2f);//
    glTexCoord2f(.5, .5);glVertex3f(0.5f, 0.6f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f(0.5f, 0.8f, 1.4f);
    //
    // top face
    // glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);glVertex3f( 0.5f, 0.8f, 1.2f);
    glTexCoord2f(0, .5);glVertex3f( 0.3f, 0.8f, 1.2f);
    glTexCoord2f(.5, .5);glVertex3f( 0.3f, 0.8f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f( 0.5f, 0.8f, 1.4f);

    // // front face  (z = 0.5f)
    // glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);glVertex3f( 0.5f,  0.8f, 1.4f);
    glTexCoord2f(0, .5);glVertex3f( 0.3f,  0.8f, 1.4f);
    glTexCoord2f(.5, .5);glVertex3f( 0.3f, 0.6f, 1.4f);
    glTexCoord2f(.5, 0);glVertex3f( 0.5f, 0.6f, 1.4f);

  glEnd();
  GLUquadricObj *quadric;
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricOrientation(quadric,GLU_INSIDE);

  // Render
  glPushMatrix();
  glTranslated(0,0,-3);
  // gluSphere(quadric,1,16,16);
  //// gluCylinder (or cone),gluDisk,gluPartialDisk

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(translateA, translateB, translateC);  // Move right and into the screen
   glRotatef(rotateA, rotateB, rotateC, rotateD);
   glScalef(scaleA, scaleB, scaleC);
   // glRotatef(45.0f, 0.5f, -0.5f, -0.0f);

   // displayEjes();
   displayPatas();
   displayAlaIzq();
   displayCuerpo();
   displayAlaDer();
   displayCabeza();
   displayPico();
   displayOjos();
   displayPapada();


   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);


}

void keyboard(unsigned char key, int x, int y) {

   switch(key){
  // rotate
  // to rotate the chicken, you use 'q', 'a', 'w', 's', 'e', 'd', 'r', and 'f'

       case 'q':
         rotateA += 5;
         break;
       case 'a':
         rotateA -= 5;
         break;
      case 'w':
        rotateB += .10;
        break;
      case 's':
        rotateB -= .10;
        break;
      case 'e':
        rotateC += .10;
        break;
      case 'd':
        rotateC -= .10;
        break;
      case 'r':
        rotateD += .10;
        break;
      case 'f':
        rotateD -= .10;
        break;

      // translate
      // to translate the chicken, you use 't', 'g', 'y', 'h', 'u', and 'j'
      case 't':
        translateA += .50;
        break;
      case 'g':
        translateA -= .50;
        break;
      case 'y':
        translateB += .50;
        break;
      case 'h':
        translateB -= .50;
        break;
      case 'u':
        translateC += .50;
        break;
      case 'j':
        translateC -= .50;
        break;

      //scale
      // To scale the chicken, you use 'i', 'k', 'o', 'l', 'p', and ';'

      case 'i':
        scaleA += .50;
        break;
      case 'k':
        scaleA -= .50;
        break;
      case 'o':
        scaleB += .50;
        break;
      case 'l':
        scaleB -= .50;
        break;
      case 'p':
        scaleC += .50;
        break;
      case ';':
        scaleC -= .50;
        break;

      case 27:
        exit(0);
        break;
      }

    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(1000, 1000);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
