#ifndef __BZK_TIME__
#define __BZK_TIME__

# ifdef WIN32
#  include <windows.h>
# endif

#include <SDL/SDL.h>

class BZK_Time
{
 public:
   BZK_Time(int interval);
   void Reset();  
   void Start();
   void Refresh();
   Uint32 left_time();
   void nextStep();
   long getFPS();
   long getElapsedTime();
   long iFPS;
   long iFrame;
   long iThisTime;
   long iStartTime;
   long next_time;
   long oldTime;
   long elapsedTime;
   int  tickInterval;
};

#endif
