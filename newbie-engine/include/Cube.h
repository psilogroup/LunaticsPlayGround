#ifndef __CUBE__
#define __CUBE__
# ifdef WIN32
#  include <windows.h>
# endif
#include "Object.h"
#include "TexturePCX.h"
class Cube:public Object
{
 public:
   Cube();
   virtual void Draw();
   virtual void Update();
   bool useTexture;
   TexturePCX *texture;



   virtual ~Cube(){};
};
#endif
