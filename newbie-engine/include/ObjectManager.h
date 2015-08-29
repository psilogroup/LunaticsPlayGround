#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__

#ifdef WIN32
#include <windows.h>
#endif

#include <SDL/SDL.h>
#include "BZK_List.h"
#include "Object.h"

class ObjectManager
{
 public:
   ObjectManager();
   void add(Object *o);
   int totalObjects();
   void Erase();
   void Update();
   void Draw();
   BZK_List <Object*> iActors;
};
#endif
