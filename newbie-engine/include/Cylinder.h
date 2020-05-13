#ifndef __CYLINDER__
#define __CYLINDER__

#include "Object.h"
#include "Texture.h"

class Cylinder:public Object
{
 public:
  float radius;
  float height;
  float slices;
  float stacks;

   Cylinder(float radius_, float height_, float slices_, float stacks_);
   void MakeGeom(dSpaceID space);
   void MakeBody(dWorldID world);
   virtual void Draw();
   virtual void Update();
   bool useTexture;
   Texture *texture;



   virtual ~Cylinder(){};
};
#endif

