#ifndef __PLANE_C__
#define __PLANE_C__
#ifdef WIN32
#include <windows.h>
#endif
#include "vec3d.h"
#include "Object.h"

class Plane:public Object
{
   vec3d iA;
   vec3d iB;
   vec3d iC;
   vec3d iD;
   Plane(vec3d a,vec3d b,vec3d c,vec3d d);
   virtual void MakeBody(dWorldID world);
   virtual void MakeGeom(dSpaceID space);
   virtual void Make();
};

#endif


   
