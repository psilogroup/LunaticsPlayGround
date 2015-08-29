#ifndef __MATERIAL__
#define __MATERIAL__
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <string.h>
class Material
{
      public:
        GLfloat Ka[3];
        GLfloat Kd[3];
        GLfloat Ks[3];
        GLfloat Ke[3];
        GLfloat ShiniNess;
        Material();
        void Build();
};
#endif
