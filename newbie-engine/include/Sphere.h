#ifndef __SPHERE__
#define __SPHERE__
#ifdef WIN32
#include <windows.h>
#endif
#include <ode/ode.h>
#include "Object.h"

class Sphere:public Object
{
 public:
   float iRadius;
   int iSlices;
   int iStacks;
   Sphere(float r,int slice,int stack);
   virtual void MakeBody(dWorldID world);
   virtual void MakeGeom(dSpaceID space);
   virtual void Draw();
   virtual void Update();

};
#endif
