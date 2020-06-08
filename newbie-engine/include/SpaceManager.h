#ifndef __SPACE_MANAGER__
#define __SPACE__MANAGER__
#ifdef WIN32
#include <windows.h>
#endif
#include "BZK_List.h"
#include "Space.h"
#include "baselib.h"
#include "Shader.h"
class SpaceManager
{
 public:
   SpaceManager();
   void Add(Space *s);
   void Update();
   void Draw(Shader *shader);
   BZK_List  <Space*> iSpaces;
};

#endif
