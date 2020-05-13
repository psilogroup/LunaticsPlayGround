
#ifndef TEXTURE_H
#define TEXTURE_H

#include "baselib.h"





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
