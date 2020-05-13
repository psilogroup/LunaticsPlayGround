#ifndef __SDLFUNC__
#define __SDLFUNC__
#ifdef WIN32
#include <windows.h>
#endif
#include <SDL/SDL.h>

Uint32 GetPixel(SDL_Surface *surface,int x,int y);
Uint32 PutPixel(SDL_Surface *surface,int x,int y,Uint32 pixel);
void Hline(SDL_Surface *surface,int x1,int x2,int y,Uint32 cor);
void Vline(SDL_Surface *surface,int y1,int y2,int x,Uint32 cor);

#endif
