#include "BZK_Time.h"

BZK_Time::BZK_Time(int interval)
{
  Reset();
  next_time = SDL_GetTicks() + interval;
  tickInterval = interval;
}

void BZK_Time::Reset()
{
  iStartTime = 0;
  iThisTime = 0;
  iFPS = 0;
  iFrame = 0;
}

void BZK_Time::Start()
{
  iStartTime = SDL_GetTicks();
}

Uint32 BZK_Time::left_time()
{
  Uint32 now = SDL_GetTicks();
  if (next_time <= now)
    return 0;
  else
    return next_time - now;
}

void BZK_Time::Refresh()
{
   oldTime = iThisTime;
   iThisTime = SDL_GetTicks();
   iFPS = (int)((float)iFrame / (iThisTime - iStartTime) * 1000.0);
   elapsedTime = (iThisTime - oldTime);
   iFrame++;


}

void BZK_Time::nextStep()
{
  Refresh();
  SDL_Delay(left_time());
  next_time += tickInterval;
}

long BZK_Time::getFPS()
{
  return iFPS;
}

long BZK_Time:: getElapsedTime()
{
   return elapsedTime;
}
