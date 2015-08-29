#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdlfunc.h"

Uint32 GetPixel(SDL_Surface *surface,int x,int y)
{
   int bpp = surface->format->BytesPerPixel;
   Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
   
   switch(bpp)
     {
      case 1:
	return *p;
      
      case 2:
	return *(Uint16 *)p;
      case 3:
	  if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      	     return p[0] << 16 | p[1] << 8 | p[2];
	else
	  return p[0] | p[1] << 8 | p[2] << 16;
      case 4:
	return *(Uint32 *)p;
      
      default:
	return 0;
     }
}


Uint32 PutPixel(SDL_Surface *surface,int x,int y,Uint32 pixel)
{
   int bpp = surface->format->BytesPerPixel;
   Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
   
   switch (bpp)
     {
      case 1:
	*p = pixel;
	break;
      case 2:
	*(Uint16 *)p = pixel;
	break;
      case 3:
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	  {
	     p[0] = (pixel >> 16) & 0xff;
	     p[1] = (pixel >> 8) & 0xff;
	     p[2] = pixel & 0xff;
	  }
	else
	  {
	     p[0] = pixel & 0xff;
	     p[1] = (pixel >> 8) & 0xff;
	     p[2] = (pixel >> 16) & 0xff;
	  }
	break;
      case 4:
	*(Uint32 *)p = pixel;
	break;
     }
   return 0;
}

/*desenha linha horizontal*/

void Vline(SDL_Surface *surface,int x1,int x2,int y,Uint32 cor)
{
   int Count;
   
   for(Count=x1;Count<x2;Count++)
     {
	PutPixel(surface,Count,y,cor);
     }
   
}

/*desenha linha vertical */

void Hline (SDL_Surface *surface,int y1,int y2,int x,Uint32 cor)
{
   int Count;
   
   for (Count=y1;Count<y2;Count++)
     {
	PutPixel(surface,x,Count,cor);
     }
}
