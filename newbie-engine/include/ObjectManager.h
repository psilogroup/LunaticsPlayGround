#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__

#include "baselib.h"
#include "BZK_List.h"
#include "Object.h"
#include "Shader.h"

class ObjectManager
{
 public:
   ObjectManager();
   void add(Object *o);
   int totalObjects();
   void Erase();
   void Update();
   void Draw(Shader *shader);
   BZK_List <Object*> iActors;
};
#endif
