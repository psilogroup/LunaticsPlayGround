#ifndef __DEF__
#define __DEF__

#define NOMINMAX
#include <Windows.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <ode/ode.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <freeglut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define DISABLE_THRESHOLD 0.08
#define AUTO_DISABLE_STEPS 10

#define RAD2DEG(a) ((a) * (180.0f / M_PI))
#define DEG2RAD(a) ((a) * (M_PI / 180.0f))

static void setColor(float k[3],float r,float g,float b)
{
    k[0] = r;
    k[1] = g;
    k[2] = b;
    k[3] = 0.0;
}

static void setTransform (const float pos[3], const float R[12])
{
  float matrix[16];
  matrix[0]=R[0];
  matrix[1]=R[4];
  matrix[2]=R[8];
  matrix[3]=0;
  matrix[4]=R[1];
  matrix[5]=R[5];
  matrix[6]=R[9];
  matrix[7]=0;
  matrix[8]=R[2];
  matrix[9]=R[6];
  matrix[10]=R[10];
  matrix[11]=0;
  matrix[12]=pos[0];
  matrix[13]=pos[1];
  matrix[14]=pos[2];
  matrix[15]=1;
  
  glMultMatrixf (matrix);
}


#endif
