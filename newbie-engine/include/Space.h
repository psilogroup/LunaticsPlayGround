#ifndef __SPACE__
#define __SPACE__
#ifdef WIN32
#include <windows.h>
#endif
#include "ObjectManager.h"
#include <ode/ode.h>

class Space
{
 public:
   Space(dSpaceID spc);
   void addObject(Object *o);
   void Update();
   void Draw();
   int getNumberOfObjects();
   ObjectManager iObjects;
   dSpaceID iSpace;
};

#endif

