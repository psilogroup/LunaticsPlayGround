#ifndef __COMMAND__
#define __COMMAND__
# ifdef WIN32
#  include <windows.h>
# endif
#include "BZK_List.h"
typedef struct
{
   char *name;
   void *value;
}Parameter;

class Command
{
 public:
   char *name;
   BZK_List <Parameter*> Parameters;
   setFunc( *(func)(BZK_List <Parameters*> p));
   Command(char *nm);
   bool Execute();
};
#endif
