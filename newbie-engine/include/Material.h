#ifndef __MATERIAL__
#define __MATERIAL__

#include <windows.h>

//#include <GL/gl.h>
#include <string.h>
class Material
{
      public:
        float Ka[3];
        float Kd[3];
        float Ks[3];
        float Ke[3];
        float ShiniNess;
        Material();
        void Build();
};
#endif
