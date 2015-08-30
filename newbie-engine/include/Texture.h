
#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef WIN32
#include <windows.h>
#endif
#include <SDL2/SDL.h>
//#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>


/**< Geracao de Texturas */
class Texture
{
public:
Texture(){};
	Texture(const char *filename);
    void bind ();
	void end();
	virtual ~Texture();
	SDL_Surface* image;
	GLuint name;
	int id;
};

#endif // TEXTURE_H
