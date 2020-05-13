#ifndef __CONSOLE__
#define __CONSOLE__

#include "BZK_List.h"
#define MAX_LINE_SIZE 256
#include "Command.h"
# ifdef WIN32
#  include <windows.h>
# endif
class Console
{
 public:
   bool active;
   int width;
   BZK_List <char*> Lines;
   char CurrentLine[MAX_LINE_SIZE];
   int x,y;
   BZK_List <Command*> Commands;
};
#endif
